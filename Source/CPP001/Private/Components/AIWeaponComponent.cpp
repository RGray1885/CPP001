// Trying to make a simple game using c++ and a lot of help


#include "Components/AIWeaponComponent.h"
#include "Weapon/BaseWeapon.h"
DEFINE_LOG_CATEGORY_STATIC(LogAIWeapon, All, All);

void UAIWeaponComponent::FireWeapon()
{
    if (!CanFire())
        return;
    if (!CurrentWeapon->HaveNoAmmoToShoot()&&
        !ReloadInProgress)
    {
        CurrentWeapon->StartFire();
    }
    else
    {
        UE_LOG(LogAIWeapon,Error,TEXT("No more ammo"));
        NextWeapon();
    }
}

void UAIWeaponComponent::NextWeapon()
{
        if (!CanEquip())
        return;
    if (ReloadInProgress)
        return;
    StopFiring();
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    
    while (NextIndex != CurrentWeaponIndex)
    {
        if (Weapons[NextIndex]->HaveAnyAmmo())
            break;
        NextIndex=(NextIndex+1) % Weapons.Num();
    }
    
    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        if (!EquipInProgress)
        EquipWeapon(CurrentWeaponIndex);
    }
}
