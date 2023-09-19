// Trying to make a simple game using c++ and a lot of help


#include "Weapon/RifleWeapon.h"
#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

ARifleWeapon::ARifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ARifleWeapon::StartFire()
{

    TriggerPulled = true;
    if (Super::HaveNoAmmoToShoot()||Super::IsClipEmpty())
        return;
    
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
    SetFXActive(false);
}

void ARifleWeapon::Zoom(bool Enabled)
{
    const APlayerController *Controller = Cast<APlayerController>(GetController());
    if (!IsValid(Controller)||!IsValid(Controller->PlayerCameraManager))
    {
        return;
    }
    else
    {
        if (Enabled)
        {
            DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
        }
        Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
    }
}

void ARifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ARifleWeapon::MakeShot()
{
    if (Super::HaveNoAmmoToShoot()||Super::IsClipEmpty())
        return;
    UE_LOG(LogTemp, Error, TEXT("Making Shot"));
    if (!TriggerPulled)
        return;
    if (!GetWorld())
        return;
    InitFX();

    FVector TraceStart;                         
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;
    FHitResult HitResult;
    Super::MakeShot();
    MakeHit(HitResult, TraceStart, TraceEnd);
    FVector TraceFXEnd = TraceEnd;

    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        //DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0, 3);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 32, FColor::Red, false, 3.0f, 0, 3);
        WeaponFXComponent->PlayImpactFX(HitResult);
        MakeDamage(HitResult);
    }
    SpawnTraceFX(GetMuzzleLocation(), TraceFXEnd);
    /* else
    {
        SpawnTraceFX(GetMuzzleLocation(), TraceEnd);

        //DrawDebugLine(GetWorld(), GetMuzzleLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3);
    }*/
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
void ARifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    if (!IsValid(FireAudioComponent))
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    SetFXActive(true);
}
void ARifleWeapon::SetFXActive(bool IsActive)
{
    if (MuzzleFXComponent)
    {
        //MuzzleFXComponent->DestroyComponent(true);
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }
    if (IsValid(FireAudioComponent))
    {
        if (IsActive && FireAudioComponent->IsPlaying())
            return; // without it loop sound will start play every time when makeshot() fires
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
    }
}
void ARifleWeapon::SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),TraceFX,TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}
void ARifleWeapon::MakeDamage(const FHitResult &HitResult)
{
    const auto HitActor = HitResult.GetActor();
    if (!HitActor)
        return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    HitActor->TakeDamage(DamagePerHit, PointDamageEvent, GetController(), this);
}

AController *ARifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}