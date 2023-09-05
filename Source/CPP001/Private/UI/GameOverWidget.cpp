// Trying to make a simple game using c++ and a lot of help


#include "UI/GameOverWidget.h"
#include "ShooterGameModeBase.h"
#include "Player/BasePlayerState.h"
#include "UI/PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "ProjectUtils.h"

bool UGameOverWidget::Initialize()
{
    if (GetWorld())
    {
        const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverWidget::OnMatchStateChanged);
        }
    }
    return Super::Initialize();
}

void UGameOverWidget::OnMatchStateChanged(EMatchState State)
{
    if (State == EMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void UGameOverWidget::UpdatePlayersStat()
{
    if (!GetWorld() || !PlayerStatBox)
        return;
    
    PlayerStatBox->ClearChildren();
    
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ABasePlayerState>(Controller->PlayerState);
        if (!PlayerState)
            return;

        const auto PlayerStatRowWidget = CreateWidget<UPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget)
            continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(ProjectUtils::TextFromInt(PlayerState->GetKillCount())); //FText::FromString(FString::FromInt(PlayerState->GetKillCount())));
        PlayerStatRowWidget->SetDeaths(ProjectUtils::TextFromInt(PlayerState->GetDeathCount())); // FText::FromString(FString::FromInt(PlayerState->GetDeathCount())));
        PlayerStatRowWidget->SetTeam(ProjectUtils::TextFromInt(PlayerState->GetTeamID())); // FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }

}
