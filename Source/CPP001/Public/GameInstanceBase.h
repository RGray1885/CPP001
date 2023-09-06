// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceBase.generated.h"

/**
 *
 */
UCLASS()
class CPP001_API UGameInstanceBase : public UGameInstance
{
    GENERATED_BODY()

  public:
    FName GetStartupLevelName() const
    {
        return StartupLevelName;
    }
    FName GetMenuLevelName() const
    {
        return MainMenuLevelName;
    }

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MainMenuLevelName = NAME_None;
};
