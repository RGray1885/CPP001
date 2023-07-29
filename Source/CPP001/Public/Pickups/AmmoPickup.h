// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "ProjectCoreTypes.h"
#include "AmmoPickup.generated.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);
class UWeaponComponent;
class ABaseWeapon;

/**
 * 
 */
UCLASS()
class CPP001_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
    virtual bool GivePickupTo(APawn *PlayerPawn) override;

 protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
  FAmmoPickupData AmmoPickup;

    
};
