// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "UI/BaseWidget.h"
#include "CoreMinimal.h"
#include "PauseWidget.generated.h"

/**
 *
 */

class UButton;
UCLASS()
class CPP001_API UPauseWidget : public UBaseWidget
{
    GENERATED_BODY()

  protected:
    virtual void NativeOnInitialized() override;

  protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

  private:
    UFUNCTION()
    void OnClearPause();
};
