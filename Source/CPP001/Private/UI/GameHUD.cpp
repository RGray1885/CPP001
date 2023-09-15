// Trying to make a simple game using c++ and a lot of help

#include "UI/GameHUD.h"
#include "Engine/Canvas.h"
#include "UI/BaseWidget.h"
#include "ShooterGameModeBase.h"


DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, All);


void AGameHUD::DrawHUD()
{
    Super::DrawHUD();
   
    //DrawCrosshair();
}


void AGameHUD::BeginPlay()
{
    Super::BeginPlay();
    GameWidgets.Add(EMatchState::InProgress, CreateWidget<UBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EMatchState::Pause, CreateWidget<UBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EMatchState::GameOver, CreateWidget<UBaseWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget)
            continue;
        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AGameHUD::OnMatchStateChanged);
        }
    }
}

void AGameHUD::DrawCrosshair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);
    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void AGameHUD::OnMatchStateChanged(EMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }

    UE_LOG(LogGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
