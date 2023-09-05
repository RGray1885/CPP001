// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "PauseWidget.generated.h"

/**
 *
 */

class UButton;
UCLASS()
class CPP001_API UPauseWidget : public UUserWidget
{
    GENERATED_BODY()

  protected:
    virtual bool Initialize() override;

  protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

  private:
    UFUNCTION()
    void OnClearPause();
};
