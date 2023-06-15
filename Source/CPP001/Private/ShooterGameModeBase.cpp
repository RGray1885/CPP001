// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"
#include "Player/BaseCharacter.h"
#include "Player/BasePlayerController.h"


AShooterGameModeBase::AShooterGameModeBase()
{
	//Set default classes for player pawn and player controller
    DefaultPawnClass = ABaseCharacter::StaticClass();
    PlayerControllerClass = ABasePlayerController::StaticClass();
}
