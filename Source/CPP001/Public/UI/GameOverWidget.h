// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "ProjectCoreTypes.h"
#include "GameOverWidget.generated.h"

/**
 *
 */

class UVerticalBox;
class UButton;
UCLASS()
class CPP001_API UGameOverWidget : public UUserWidget
{
    GENERATED_BODY()


  protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox *PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton *RestartButton;

    virtual void NativeOnInitialized() override;

  private:
    void OnMatchStateChanged(EMatchState State);
    void UpdatePlayersStat();
    UFUNCTION()
    void RestartLevel();
};
