// Trying to make a simple game using c++ and a lot of help


#include "Weapon/LauncherWeapon.h"
#include "Weapon/ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"

void ALauncherWeapon::StartFire()
{
    MakeShot();
}

void ALauncherWeapon::MakeShot()
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
    //set projectile params
    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}


