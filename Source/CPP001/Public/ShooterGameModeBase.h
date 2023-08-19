// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectCoreTypes.h"
#include "ShooterGameModeBase.generated.h"

/**
 *
 */

class AAIController;

UCLASS()
class CPP001_API AShooterGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

  public:
    AShooterGameModeBase();

    virtual void StartPlay() override;
    virtual UClass *GetDefaultPawnClassForController_Implementation(AController *InController) override;

    protected:
    UPROPERTY(EditDefaultsOnly, Category = "GameOptions")
    TSubclassOf<AAIController> AIControllerClass;
    UPROPERTY(EditDefaultsOnly, Category = "GameOptions")
    TSubclassOf<APawn> AIPawnClass;
    UPROPERTY(EditDefaultsOnly, Category = "GameOptions")
    FGameData GameData;

    private:
    void SpawnBots();
};
