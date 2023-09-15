// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "SpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API USpectatorWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& RespawnCountdown)const;
};
