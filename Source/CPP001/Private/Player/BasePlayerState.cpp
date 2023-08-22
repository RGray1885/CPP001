// Trying to make a simple game using c++ and a lot of help


#include "Player/BasePlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePlayerState,All,All)
void ABasePlayerState::LogInfo()
{
    UE_LOG(LogBasePlayerState, Display,TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillCount, DeathCount);
}
