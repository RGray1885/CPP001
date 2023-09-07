// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectCoreTypes.h"
#include "LevelIconWidget.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class UImage;

UCLASS()
class CPP001_API ULevelIconWidget : public UUserWidget
{
	GENERATED_BODY()
	
		protected:
    UPROPERTY(meta = (BindWidget))
    UButton *LevelButton;
    UPROPERTY(meta = (BindWidget))
    UTextBlock *LevelName;
    UPROPERTY(meta = (BindWidget))
    UImage *LevelImage=nullptr;
    UPROPERTY(meta = (BindWidget))
    UImage *FrameImage;

    virtual void NativeOnInitialized() override;

    private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelIconClicked();

    public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData &Data);
    
    FLevelData GetLevelData() const
    {
        return LevelData;
    }

    void SetSelected(bool IsSelected);
};
