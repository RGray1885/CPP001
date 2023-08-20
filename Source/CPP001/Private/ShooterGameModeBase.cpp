// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"
#include "UI/GameHUD.h"
#include "AIController.h"


DEFINE_LOG_CATEGORY_STATIC(LogShooterGameModeBase, All, All);


AShooterGameModeBase::AShooterGameModeBase()
{
	//Set default classes for player pawn and player controller
    DefaultPawnClass = ABaseCharacter::StaticClass();
    PlayerControllerClass = ABasePlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();

    CurrentRound = 1;
    StartRound();

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

    for (int32 i = 0; i < GameData.PlayersNum - 1;++i)
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
    UE_LOG(LogShooterGameModeBase, Display, TEXT("Time: %i /Round: %i/%i"), RoundTimeLeft, CurrentRound,
           GameData.RoundsNum);

   // const auto TimerRate = GetWorldTimerManager().GetTimerRate(RoundTimerHandle);
   // RoundTimeLeft -= TimerRate;

    if (--RoundTimeLeft == 0)
    {
        GetWorldTimerManager().ClearTimer(RoundTimerHandle);
        if(CurrentRound+1<=GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogShooterGameModeBase, Display, TEXT("======= GAME OVER ======="))
        }

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
}
