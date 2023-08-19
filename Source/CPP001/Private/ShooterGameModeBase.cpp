// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"
#include "UI/GameHUD.h"
#include "AIController.h"



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
