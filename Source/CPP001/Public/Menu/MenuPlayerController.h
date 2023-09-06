// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
  protected:
    virtual void BeginPlay() override;
};
