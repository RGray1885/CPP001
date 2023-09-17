// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundFunctionLibrary.generated.h"

/**
 * 
 */

class USoundClass;
UCLASS()
class CPP001_API USoundFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

		public:
    UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass *SoundClass, float Volume);
    UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass *SoundClass);
};
