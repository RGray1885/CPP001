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
    if (!GetWorld())
        return;
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);
    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleLocation()).GetSafeNormal();
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    // auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass,
    // SpawnTransform);
    AProjectileRocket *Projectile = GetWorld()->SpawnActorDeferred<AProjectileRocket>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetDamageRadius(DamageRadius);
        Projectile->SetDamageAmount(DamagePerHit);
        Projectile->SetOwner(GetOwner());
        Projectile->SetDoFullDamage(DoFullDamage);
        Projectile->SetProjectileLifeTime(ProjectileLifeTime);
        Projectile->FinishSpawning(SpawnTransform);
        
    }
    // set projectile params
   // UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}


