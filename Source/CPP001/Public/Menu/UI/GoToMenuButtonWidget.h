// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoToMenuButtonWidget.generated.h"

/**
 * 
 */

class UButton;
UCLASS()
class CPP001_API UGoToMenuButtonWidget : public UUserWidget
{
    GENERATED_BODY()
  
protected:
        virtual void NativeOnInitialized() override;

        UPROPERTY(meta = (BindWidget))
        UButton *MainMenuButton;
        private:
        UFUNCTION()
        void GoToMainMenu();

};
