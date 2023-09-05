// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectCoreTypes.h"
#include "GameHUD.generated.h"

/**
 *
 */
UCLASS()
class CPP001_API AGameHUD : public AHUD
{
    GENERATED_BODY()
  public:
    virtual void DrawHUD() override;
    

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
    UUserWidget *PlayerHUDWidget;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;
    virtual void BeginPlay() override;


  private:

      UPROPERTY()
    TMap<EMatchState, UUserWidget *> GameWidgets;

      UPROPERTY()
    UUserWidget *CurrentWidget = nullptr;

    void DrawCrosshair();
    void OnMatchStateChanged(EMatchState State);
};
