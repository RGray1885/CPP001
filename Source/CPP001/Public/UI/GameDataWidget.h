// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameDataWidget.generated.h"

/**
 * 
 */
class ABasePlayerState;
class AShooterGameModeBase;

UCLASS()
class CPP001_API UGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void GetGameStatistics(int32 &KillsCount, int32 &DeathsCount, int32 &RoundTime, int32 &CurrentRound,
                           int32 &RoundsTotal) const;
};