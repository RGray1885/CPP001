// Trying to make a simple game using c++ and a lot of help


#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

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
    checkf(DefaultAmmo.ClipSize > 0, TEXT("Ammo in clip should be greater than zero"));
    checkf(DefaultAmmo.TotalAmmo > 0, TEXT("Ammo in total should be greater than zero"));
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
    //SpawnMuzzleFX();
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
    const auto OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter)
        return false;

    if (OwnerCharacter->IsPlayerControlled())
    {
        const auto Controller = GetPlayerController();
        if (!Controller)
            return false;
        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = GetMuzzleLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }
    
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
    CollisionParams.bReturnPhysicalMaterial = true;

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,CollisionParams);
   
}
void ABaseWeapon::ConsumeAmmo()
{
    CurrentAmmo.ClipSize-=CurrentAmmo.AmmoPerShotConsumption;
    if (IsClipEmpty())
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Empty Clip"));
        OnClipEmpty.Broadcast(this);
    }
    
    
    LogAmmo();
    //if (IsClipEmpty()&&!HaveNoAmmoToShoot())
    //{
    //    ReloadClip();
    //}
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
    if (CurrentAmmo.TotalAmmo == 0 && IsClipEmpty())
    {
        UE_LOG(LogBaseWeapon, Error, TEXT("Have no ammo"));
    }
        return CurrentAmmo.TotalAmmo==0 && !CurrentAmmo.HasInfiniteAmmo && IsClipEmpty();
    
    
}

//bool ABaseWeapon::IsClipNotFull() const
//{
  //      return CurrentAmmo.ClipSize<DefaultAmmo.ClipSize;
//}

void ABaseWeapon::ReloadClip()
{
    if (CurrentAmmo.HasInfiniteAmmo)
    {
        CurrentAmmo.ClipSize = DefaultAmmo.ClipSize;
        UE_LOG(LogBaseWeapon, Display, TEXT("Infinite ammo, reload successful"));

    }
    else if (CurrentAmmo.TotalAmmo >= DefaultAmmo.ClipSize && IsClipEmpty())
    {
        CurrentAmmo.ClipSize = DefaultAmmo.ClipSize;
        CurrentAmmo.TotalAmmo -= DefaultAmmo.ClipSize;
        UE_LOG(LogBaseWeapon, Display, TEXT("Ammo in inventory more than clip size, reload successful"));


    }
    else if (CurrentAmmo.TotalAmmo < DefaultAmmo.ClipSize && IsClipEmpty())
    {
        CurrentAmmo.ClipSize = CurrentAmmo.TotalAmmo;
        CurrentAmmo.TotalAmmo = 0;
        UE_LOG(LogBaseWeapon, Warning, TEXT("Not enough ammo for full clip, reload successful"));

    }
    else if (CurrentAmmo.TotalAmmo >= (DefaultAmmo.ClipSize - CurrentAmmo.ClipSize)&&IsClipNotFull())
    {
        CurrentAmmo.TotalAmmo = FMath::Clamp((CurrentAmmo.TotalAmmo-(DefaultAmmo.ClipSize - CurrentAmmo.ClipSize)),0
            ,DefaultAmmo.TotalAmmo);
        CurrentAmmo.ClipSize = DefaultAmmo.ClipSize;
        if (CurrentAmmo.TotalAmmo > DefaultAmmo.TotalAmmo)
            CurrentAmmo.TotalAmmo = DefaultAmmo.TotalAmmo;
            UE_LOG(LogBaseWeapon, Warning, TEXT("Total ammo more than clip diff, reload successful"));
    }
    else if (CurrentAmmo.TotalAmmo < (DefaultAmmo.ClipSize - CurrentAmmo.ClipSize) && IsClipNotFull())
    {
        CurrentAmmo.ClipSize += CurrentAmmo.TotalAmmo;
        CurrentAmmo.TotalAmmo = 0;
        UE_LOG(LogBaseWeapon, Warning, TEXT("Total ammo less than clip diff, reload successful"));
    }
    else if (CurrentAmmo.ClipSize == DefaultAmmo.ClipSize)
    {
        return;
    }
    
    LogAmmo();
}

void ABaseWeapon::LogAmmo()
{
        FString AmmoInfoLog = "Ammo: " + FString::FromInt(CurrentAmmo.ClipSize) + "/";
        AmmoInfoLog += CurrentAmmo.HasInfiniteAmmo ? "Infinite" : FString::FromInt(CurrentAmmo.TotalAmmo);
        UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfoLog);
}

UNiagaraComponent *ABaseWeapon::SpawnMuzzleFX()
{
        return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, WeaponMesh, MuzzleSocketName,
                                                            //WeaponMesh->GetSocketLocation(MuzzleSocketName), 
                                                            FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget,true);
        
}


void ABaseWeapon::Zoom(bool Enabled)
{
}

void ABaseWeapon::Reload()
{
        if (!HaveNoAmmoToShoot())
        ReloadClip();
}

FString ABaseWeapon::GetCurrentAmmo() const
{
        FString InfAmmo = FString(TEXT("\u221e"));
        FString AmmoUI = FString::FromInt(CurrentAmmo.ClipSize) + "/";
        AmmoUI += CurrentAmmo.HasInfiniteAmmo ? InfAmmo : FString::FromInt(CurrentAmmo.TotalAmmo);
        return AmmoUI;
}

bool ABaseWeapon::RefillAmmo(int32 Amount)
{
        if (CurrentAmmo.TotalAmmo < DefaultAmmo.TotalAmmo && !CurrentAmmo.HasInfiniteAmmo&&(!IsClipEmpty() && !IsClipNotFull()))
        {
        CurrentAmmo.TotalAmmo =
            FMath::Clamp((CurrentAmmo.TotalAmmo + Amount), CurrentAmmo.TotalAmmo, DefaultAmmo.TotalAmmo);
        return true;
        }
        else if (CurrentAmmo.TotalAmmo <= DefaultAmmo.TotalAmmo && !CurrentAmmo.HasInfiniteAmmo && (IsClipEmpty() || IsClipNotFull()))
        {
        CurrentAmmo.TotalAmmo =
            FMath::Clamp((CurrentAmmo.TotalAmmo + Amount), CurrentAmmo.TotalAmmo, (DefaultAmmo.TotalAmmo+(FMath::Clamp(Amount,0,DefaultAmmo.ClipSize-CurrentAmmo.ClipSize))));
        OnClipEmpty.Broadcast(this);
        return true;
        }
        else
        {
        UE_LOG(LogBaseWeapon, Error, TEXT("Can't carry anymore ammo"));
        return false;
        }
}
