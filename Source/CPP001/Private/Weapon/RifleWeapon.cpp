// Trying to make a simple game using c++ and a lot of help


#include "Weapon/RifleWeapon.h"

void ARifleWeapon::StartFire()
{

    TriggerPulled = true;
    if (AutoFireAvailable)
    {
        GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &ARifleWeapon::MakeShot, WeaponRateOfFire, TriggerPulled,
                                               WeaponFireDelay);
    }
    else
    {
        MakeShot();
    }
}

void ARifleWeapon::StopFire()
{
    TriggerPulled = false;
    GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
}

void ARifleWeapon::MakeShot()
{
    if (!TriggerPulled)
        return;
    if (!GetWorld())
        return;
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0, 3);

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 32, FColor::Red, false, 3.0f, 0, 3);
        MakeDamage(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3);
    }
}
bool ARifleWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{ 
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation))return false;                    

    TraceStart = ViewLocation;                              
    const auto FireHalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(),FireHalfRad);

    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}
void ARifleWeapon::MakeDamage(const FHitResult &HitResult)
{
    const auto HitActor = HitResult.GetActor();
    if (!HitActor)
        return;
    HitActor->TakeDamage(DamagePerHit, FDamageEvent{}, GetPlayerController(), this);
}