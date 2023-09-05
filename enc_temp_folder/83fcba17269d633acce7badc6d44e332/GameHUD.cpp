// Trying to make a simple game using c++ and a lot of help

#include "UI/GameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "ShooterGameModeBase.h"


DEFINE_LOG_CATEGORY_STATIC(LogGameHUD, All, All);


void AGameHUD::DrawHUD()
{
    Super::DrawHUD();
   
    //DrawCrosshair();
}


void AGameHUD::BeginPlay()
{
    PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
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
    UE_LOG(LogGameHUD, Display, TEXT("Match statechanged: %s"), *UEnum::GetValueAsString(State));
}