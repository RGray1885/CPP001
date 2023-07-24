// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPickup.generated.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);
/**
 * 
 */
UCLASS()
class CPP001_API AHealthPickup : public ABasePickup
{
    GENERATED_BODY()
  private:
        virtual bool GivePickupTo(APawn *PlayerPawn) override;
};
