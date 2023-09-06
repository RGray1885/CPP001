// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class CPP001_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
		protected:
    UPROPERTY(meta = (BindWidget))
    UButton *StartGameButton;
	UPROPERTY(meta = (BindWidget))
    UButton *QuitGameButton;

	virtual void NativeOnInitialized() override;

	private:
    UFUNCTION()
    void OnStartGame();
    UFUNCTION()
    void OnQuitGame();
};
