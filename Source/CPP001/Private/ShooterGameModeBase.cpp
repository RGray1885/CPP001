// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGameModeBase.h"
#include "AIController.h"
#include "AI/BaseAIController.h"
#include "Components/RespawnComponent.h"
#include "EngineUtils.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"
#include "Player/BasePlayerState.h"
#include "Components/WeaponComponent.h"
#include "Components/AIWeaponComponent.h"
#include "ProjectUtils.h"
#include "UI/GameHUD.h"

#include "GameInstanceBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogShooterGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

AShooterGameModeBase::AShooterGameModeBase()
{
    // Set default classes for player pawn and player controller
    DefaultPawnClass = ABaseCharacter::StaticClass();
    PlayerControllerClass = ABasePlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
    PlayerStateClass = ABasePlayerState::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();

    SetMatchState(EMatchState::InProgress);
}

UClass *AShooterGameModeBase::GetDefaultPawnClassForController_Implementation(AController *InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShooterGameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto ProjectAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(ProjectAIController);
    }
}

void AShooterGameModeBase::StartRound()
{
    RoundTimeLeft = GameData.RoundTime;
    UE_LOG(LogShooterGameModeBase, Warning, TEXT("Round %i. Fight!"), CurrentRound);
    GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AShooterGameModeBase::UpdateRoundTimer, 1.0f, true);
}

void AShooterGameModeBase::UpdateRoundTimer()
{
 //   UE_LOG(LogShooterGameModeBase, Display, TEXT("Time: %i /Round: %i/%i"), RoundTimeLeft, CurrentRound,
   //        GameData.RoundsNum);

    // const auto TimerRate = GetWorldTimerManager().GetTimerRate(RoundTimerHandle);
    // RoundTimeLeft -= TimerRate;

    if (--RoundTimeLeft == 0)
    {
        GetWorldTimerManager().ClearTimer(RoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
            GameOver();
    }
}

void AShooterGameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AShooterGameModeBase::ResetOnePlayer(AController *Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
      
}

void AShooterGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;
    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ABasePlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;
        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor AShooterGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    UE_LOG(LogShooterGameModeBase, Warning, TEXT("No color for team if: %i, set to default: %s"), TeamID,
           *GameData.DefaultTeamColor.ToString());
    return GameData.DefaultTeamColor;
}

void AShooterGameModeBase::SetPlayerColor(AController *Controller)
{
    if (!Controller)
        return;
    const auto Character = Cast<ABaseCharacter>(Controller->GetPawn());
    if (!Character)
        return;
    const auto PlayerState = Cast<ABasePlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;
    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AShooterGameModeBase::LogPlayerInfo()
{
    if (!GetWorld())
        return;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ABasePlayerState>(Controller->PlayerState);
        PlayerState->LogInfo();
    }
}

void AShooterGameModeBase::StartRespawn(AController *Controller)
{
    const auto RespawnAvaiable = RoundTimeLeft > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvaiable)
        return;
    const auto RespawnComponent = Controller->FindComponentByClass<URespawnComponent>();
    if (!RespawnComponent)
        return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void AShooterGameModeBase::GameOver()
{
    UE_LOG(LogShooterGameModeBase, Display, TEXT("======= GAME OVER ======="))
    LogPlayerInfo();
    SetMatchState(EMatchState::GameOver);

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
           const auto PawnAI = Cast<ABaseAIController>(Pawn->GetController());
           if (PawnAI)
           PawnAI->OnGameOver();
            
        }
    }
}

void AShooterGameModeBase::SetMatchState(EMatchState State)
{
    if (MatchState == State)
        return;

    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
    UE_LOG(LogShooterGameModeBase, Display, TEXT("Match state set: %s"), *UEnum::GetValueAsString(MatchState));
}

bool AShooterGameModeBase::SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (PauseSet)
    {
        SetMatchState(EMatchState::Pause);

    }

    return Super::SetPause(PC, CanUnpauseDelegate);
}

bool AShooterGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(EMatchState::InProgress);
    }
    return PauseCleared;
}

void AShooterGameModeBase::Killed(AController *KillerController, AController *VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<ABasePlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ABasePlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }
    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void AShooterGameModeBase::RespawnRequest(AController *Controller)
{
    ResetOnePlayer(Controller);
}
