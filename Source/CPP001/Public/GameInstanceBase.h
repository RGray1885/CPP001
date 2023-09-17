// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectCoreTypes.h"
#include "GameInstanceBase.generated.h"

/**
 *
 */

class USoundClass;

UCLASS()
class CPP001_API UGameInstanceBase : public UGameInstance
{
    GENERATED_BODY()

  public:
    FLevelData GetStartupLevel() const
    {
        return StartupLevel;
    }

    void SetStartupLevel(const FLevelData &Data)
    {
        StartupLevel = Data;
    }

    TArray<FLevelData> GetLevelsData() const
    {
        return LevelsData;
    }

    FName GetMenuLevelName() const
    {
        return MainMenuLevelName;
    }

    void ToggleVolume();

  protected:

    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique!"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MainMenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")

    USoundClass *MasterSoundClass;
    
private:
    FLevelData StartupLevel;
};
