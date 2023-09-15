// Trying to make a simple game using c++ and a lot of help


#include "UI/PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UPlayerStatRowWidget::SetPlayerName(const FText &Text)
{
    if (!PlayerNameTextBlock)
        return;
    PlayerNameTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetKills(const FText &Text)
{
    if (!KillsTextBlock)
        return;
    KillsTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetDeaths(const FText &Text)
{
    if (!DeathsTextBlock)
        return;
    DeathsTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetTeam(const FText &Text)
{
    if (!TeamTextBlock)
        return;
    TeamTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage)
        return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible:ESlateVisibility::Hidden);
}

void UPlayerStatRowWidget::SetTeamColor(const FLinearColor &Color)
{
    if (!IsValid(TeamImage))
    {
        return;
    }
    else
    {
        TeamImage->SetColorAndOpacity(Color);
    }
}
