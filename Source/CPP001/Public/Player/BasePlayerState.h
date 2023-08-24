// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()
	
		public:
    void SetTeamID(int32 ID)
    {
        TeamID = ID;
    }
    
    int32 GetTeamID() const
    {
        return TeamID;
    }
    
    void SetTeamColor(const FLinearColor &Color)
    {
        TeamColor = Color;
    }
    
    FLinearColor GetTeamColor() const
    {
        return TeamColor;
    }
    void AddKill()
    {
        KillCount++;
    }
    int32 GetKillCount() const
    {
        return KillCount;
    }
    void AddDeath()
    {
        DeathCount++;
    }
    int32 GetDeathCount() const
    {
        return DeathCount;
    }

    void LogInfo();
		
private:
    int32 TeamID;
    FLinearColor TeamColor;
    int32 KillCount;
    int32 DeathCount;

};
