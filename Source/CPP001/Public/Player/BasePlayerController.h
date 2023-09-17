// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectCoreTypes.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
class URespawnComponent;
UCLASS()
class CPP001_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
    
        public:
    ABasePlayerController();
    protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    URespawnComponent *RespawnComponent;

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    private:
    void OnPauseGame();
      void OnMatchStateChanged(EMatchState State);
    void OnMuteSound();
};
