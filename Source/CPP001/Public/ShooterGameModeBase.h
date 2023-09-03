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

    void Killed(AController *KillerController, AController *VictimController);
    
    int32 GetCurrentRound() const
    {
        return CurrentRound;
    }
    int32 GetTotalRounds()
    {
        return GameData.RoundsNum;
    }
    int32 GetRoundTime()
    {
        return RoundTimeLeft;
    }

    void RespawnRequest(AController* Controller);

   
    protected:
    UPROPERTY(EditDefaultsOnly, Category = "GameOptions")
    TSubclassOf<AAIController> AIControllerClass;
    UPROPERTY(EditDefaultsOnly, Category = "GameOptions")
    TSubclassOf<APawn> AIPawnClass;
    UPROPERTY(EditDefaultsOnly, Category = "GameOptions")
    FGameData GameData;

    private:
    int32 CurrentRound = 1;
    int32 RoundTimeLeft = 0;
    FTimerHandle RoundTimerHandle;
    
    void SpawnBots();
    void StartRound();
    void UpdateRoundTimer();


    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController *Controller);

    void LogPlayerInfo();

    void StartRespawn(AController *Controller);

    void GameOver();
};
