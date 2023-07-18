// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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
    virtual void BeginPlay() override;

  private:
    void DrawCrosshair();
};
