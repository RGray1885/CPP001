// Trying to make a simple game using c++ and a lot of help


#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);
// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    check(WeaponMesh);
    CurrentAmmo = DefaultAmmo;
}

void ABaseWeapon::StartFire()
{
    /*
    UE_LOG(LogBaseWeapon, Warning, TEXT("Fire!"));
    TriggerPulled = true;
    if (AutoFireAvailable)
    {
        GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &ABaseWeapon::MakeShot, WeaponRateOfFire, TriggerPulled,
                                               WeaponFireDelay);
    }
    else
    {
        MakeShot();
    } */  
}

void ABaseWeapon::StopFire()
{
    /* TriggerPulled = false;
    GetWorld()->GetTimerManager().ClearTimer(ShotTimer);*/
}




void ABaseWeapon::MakeShot()
{
    /* if (!TriggerPulled)
        return;
    if(!GetWorld()) return;
    FVector TraceStart;
    FVector TraceEnd;
    if(!GetTraceData(TraceStart,TraceEnd))return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if(HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), GetMuzzleLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0, 3);

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 32, FColor::Red, false, 3.0f, 0, 3);
        MakeDamage(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3);

    }
    */
    if (!HaveNoAmmoToShoot())
    ConsumeAmmo();
}
APlayerController *ABaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return nullptr;
    return Player->GetController<APlayerController>();
}
bool ABaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller)
        return false;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}
FVector ABaseWeapon::GetMuzzleLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}
bool ABaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{ 
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation))return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();

    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}
void ABaseWeapon::MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd)
{
    if (!GetWorld())
        return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
   
}
void ABaseWeapon::ConsumeAmmo()
{
    CurrentAmmo.ClipSize-=CurrentAmmo.AmmoPerShotConsumption;
    LogAmmo();
    if (IsClipEmpty()&&!HaveNoAmmoToShoot())
    {
        ReloadClip();
    }
}
/* bool ABaseWeapon::HaveAmmoToShoot() const
{
    return false;
}*/
/* void ABaseWeapon::AmmoConsumption()
{
    if (ShouldConsumeAmmo())
        ConsumeAmmo();
    else
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Ammo consumption not required"));
    }
}*/

bool ABaseWeapon::HaveNoAmmoToShoot() const
{
        return CurrentAmmo.TotalAmmo==0 && !CurrentAmmo.HasInfiniteAmmo && IsClipEmpty();
    
}

bool ABaseWeapon::IsClipEmpty() const
{
        return CurrentAmmo.ClipSize==0;
}

void ABaseWeapon::ReloadClip()
{
    if (CurrentAmmo.HasInfiniteAmmo)
    {
        CurrentAmmo.ClipSize = DefaultAmmo.ClipSize;
        UE_LOG(LogBaseWeapon, Display, TEXT("Infinite ammo, reload successful"));

    }
    else if (CurrentAmmo.TotalAmmo >= DefaultAmmo.ClipSize && !CurrentAmmo.HasInfiniteAmmo)
    {
        CurrentAmmo.ClipSize = DefaultAmmo.ClipSize;
        CurrentAmmo.TotalAmmo -= DefaultAmmo.ClipSize;
        UE_LOG(LogBaseWeapon, Display, TEXT("Ammo in inventory more than clip size, reload successful"));


    }
    else if (CurrentAmmo.TotalAmmo < DefaultAmmo.ClipSize && !CurrentAmmo.HasInfiniteAmmo)
    {
        CurrentAmmo.ClipSize = CurrentAmmo.TotalAmmo;
        CurrentAmmo.TotalAmmo = 0;
        UE_LOG(LogBaseWeapon, Warning, TEXT("Not enough ammo for full clip, reload successful"));

    }
    
    LogAmmo();
}

void ABaseWeapon::LogAmmo()
{
        FString AmmoInfoLog = "Ammo: " + FString::FromInt(CurrentAmmo.ClipSize) + "/";
        AmmoInfoLog += CurrentAmmo.HasInfiniteAmmo ? "Infinite" : FString::FromInt(CurrentAmmo.TotalAmmo);
        UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfoLog);
}
