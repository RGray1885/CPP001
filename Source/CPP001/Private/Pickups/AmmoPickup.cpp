// Trying to make a simple game using c++ and a lot of help


#include "Pickups/AmmoPickup.h"
#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"

bool AAmmoPickup::GivePickupTo(APawn *PlayerPawn)
{
    if (PlayerPawn)
    {
        const auto WeaponComponent = PlayerPawn->GetComponentByClass<UWeaponComponent>();
        if (WeaponComponent)
        {
            UE_LOG(LogAmmoPickup, Display, TEXT("Component Found"));
            if (!AmmoPickup.WeaponClass)
            {
                UE_LOG(LogAmmoPickup, Display, TEXT("Cast failed"));

                return false;
            }
            auto FoundWeapon = WeaponComponent->GetWeapon(AmmoPickup.WeaponClass);
            if (FoundWeapon)
            {
                UE_LOG(LogAmmoPickup, Display, TEXT("Weapon Found"));
                return FoundWeapon->RefillAmmo(AmmoPickup.Amount);
            }
            else
            {
                UE_LOG(LogAmmoPickup, Display, TEXT("Weapon not Found"));
                return false;
            }
        }
        else
            return false;

    }
    else return false;
   
   
}








