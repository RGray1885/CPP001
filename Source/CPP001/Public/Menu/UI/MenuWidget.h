// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "ProjectCoreTypes.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
class UButton;
class UHorizontalBox;
class UGameInstanceBase;
class ULevelIconWidget;

UCLASS()
class CPP001_API UMenuWidget : public UBaseWidget
{
	GENERATED_BODY()
	
		protected:
    UPROPERTY(meta = (BindWidget))
    UButton *StartGameButton;
	UPROPERTY(meta = (BindWidget))
    UButton *QuitGameButton;
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox *LevelIconsList;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelIconWidgetClass;
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation *HideAnimation;


	virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation *Animation) override;

	private:

        UPROPERTY()
      TArray<ULevelIconWidget*> LevelIconWidgets;
    
        UFUNCTION()
    void OnStartGame();
    
    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData &Data);

    UGameInstanceBase *GetGameInstance() const;
};
