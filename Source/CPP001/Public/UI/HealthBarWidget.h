// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */

class UProgressBar;
UCLASS()
class CPP001_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
		public:
    void SetHealthPercent(float Percent);
		protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar *HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentVisibilityThreshold = 0.8;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor DefaultColor = FColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor CritHealthColor = FColor::Red;
};
