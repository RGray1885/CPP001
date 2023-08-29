// Trying to make a simple game using c++ and a lot of help


#include "UI/GameDataWidget.h"
#include "Player/BasePlayerState.h"
#include "ShooterGameModeBase.h"

void UGameDataWidget::GetGameStatistics(int32 &KillsCount, int32 &DeathsCount, int32 &RoundTime, int32 &CurrentRound,
                                        int32 &RoundsTotal) const
{
    if (GetWorld())
    {
        const auto PlayerState = Cast<ABasePlayerState>(GetOwningPlayerState());
        const auto CurrentGameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());

        if (!PlayerState || !CurrentGameMode)
            return;

        KillsCount = PlayerState->GetKillCount();
        DeathsCount = PlayerState->GetDeathCount();
        RoundTime = CurrentGameMode->GetRoundTime();
        CurrentRound = CurrentGameMode->GetCurrentRound();
        RoundsTotal = CurrentGameMode->GetTotalRounds();
    }
    
}
