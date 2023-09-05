// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "Components/RespawnComponent.h"
#include "ShooterGameModeBase.h"


ABasePlayerController::ABasePlayerController()
{
    RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (GetWorld())
    {
        const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ABasePlayerController::OnMatchStateChanged);
        }
    }
}

void ABasePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent)
        return;
    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ABasePlayerController::OnPauseGame);
}

void ABasePlayerController::OnPauseGame()
{
    if (!GetWorld()||!GetWorld()->GetAuthGameMode())
        return;
    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ABasePlayerController::OnMatchStateChanged(EMatchState State)
{
    if (State == EMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}
