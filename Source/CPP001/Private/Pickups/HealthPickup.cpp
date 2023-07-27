// Trying to make a simple game using c++ and a lot of help


#include "Pickups/HealthPickup.h"
#include "Components/HealthComponent.h"

bool AHealthPickup::GivePickupTo(APawn *PlayerPawn)
{
    if (PlayerPawn)
    {
        const auto HealthComponent = PlayerPawn->GetComponentByClass<UHealthComponent>();
        if (HealthComponent && HealthComponent->ShouldHeal())
        {
            UE_LOG(LogHealthPickup, Warning, TEXT("Health picked up successfully"));
            HealthComponent->HealFromMedkit(100);
            return true;
        }
        else
        {
            UE_LOG(LogHealthPickup, Warning, TEXT("Can't pickup health"));

            return false;
        }
    }
    else
        return false;
    
}
