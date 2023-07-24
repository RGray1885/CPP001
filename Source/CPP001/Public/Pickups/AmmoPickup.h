// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
    virtual bool GivePickupTo(APawn *PlayerPawn) override;
};
