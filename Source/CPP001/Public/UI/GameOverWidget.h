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
UCLASS()
class CPP001_API UGameOverWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    virtual bool Initialize() override;

  protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox *PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

  private:
    void OnMatchStateChanged(EMatchState State);
    void UpdatePlayersStat();
};
