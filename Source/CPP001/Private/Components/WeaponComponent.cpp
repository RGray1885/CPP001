// Trying to make a simple game using c++ and a lot of help


#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "Player/BaseCharacter.h"
#include "Animations/EquipFinishedAnimNotify.h"
#include "Animations/EquipStartAnimNotify.h"
#include "Animations/ReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

const static int32 WeaponNum = 2;

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    checkf(WeaponData.Num() == WeaponNum, TEXT("Should be two weapons, no less, no more"));
    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
	// ...
	
}

void UWeaponComponent::OnEmptyClip()
{
    Reload();
}

void UWeaponComponent::FireWeapon()
{
    if (!CanFire())
    //if (!CurrentWeapon && EquipInProgress)
        return;
    //auto Player = Cast<ABaseCharacter> (CurrentWeapon->GetOwner()); //to prevent fire
    //if (!Player->GetIsRunning())                                    //during sprint or weapon change
   // if (CurrentWeapon->ShouldReload())
    //{
      //  UWeaponComponent::Reload();
    //}
    //else
    //{
   
        CurrentWeapon->StartFire();
        IsFiring = true;
   
        
    //}
    
    //if (CurrentWeapon->)
}

void UWeaponComponent::StopFiring()
{
    if (!CurrentWeapon)
    return;
    CurrentWeapon->StopFire();
    IsFiring = false;

    
}


void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon *Weapon, USceneComponent *SceneComponent,
                                            const FName &SocketName)
{
    if (!Weapon || !SceneComponent)                                                     //stop if either parameter is invalid
    return;
    FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);     //set attachment transform rules
    Weapon->AttachToComponent(SceneComponent, AttachmentRule, SocketName);              //attach weapon to socket
}
void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (!CanEquip())
    return;
    if (CurrentWeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
    UE_LOG(LogWeaponComponent, Error, TEXT("Invalid Weapon Index"))
    return;
    }
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner()); // the same as in SpawnWeapons method
    if (!OwnerCharacter||Weapons.IsEmpty())                           
    return;
    if (CurrentWeapon)                                                                      //if current weapon is valid
    {
    AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName); //attach to another socket (on back by default)
    }
    CurrentWeapon = Weapons[WeaponIndex];                                                   //get new weapon from array
    //CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData &Data) { // lambda-functions -> look for them
        return Data.WeaponClass == CurrentWeapon->GetClass();                                 //
    });
    
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponEquipSocketName);  //attach new weapon to hands socket
    PlayAnimMontage(EquipAnimMontage);
    
    
}



void UWeaponComponent::SpawnWeapons()                                                       //spawning weapon
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());                             //Get component's owner->cast to ACharacterClass->promote to var OwnerCharacter of class ACharacter
    if (!OwnerCharacter||!GetWorld()||WeaponData.IsEmpty())                             //don't spawn if owner or world is invalid, or weapon classes array is empty
        return;
    for (auto OneWeaponData:WeaponData)                                                 //spawn WeaponClasses array elements
    {
    auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(OneWeaponData.WeaponClass);                        //spawn actor of class ABaseWeapon
        if (!Weapon)
            continue;
        Weapon->OnClipEmpty.AddUObject(this, &UWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(OwnerCharacter);                                                   //set weapon's owner
        Weapons.Add(Weapon);                                                                //add to weapons array
        AttachWeaponToSocket(Weapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName);    //attach on back
    }
}



void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)        // what to do on death
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::NextWeapon()                                    //Cycle through weapons in Weapons array
{
    if (!CanEquip()||!CurrentWeapon)
    //if (EquipInProgress || !CurrentWeapon)
        //return;
    //if ()                                                //Cycle if CurrentWeapon is Valid
        return;
    if (ReloadInProgress)
        return;
    StopFiring();                                                      //Prevent weapon from firing during switching
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();     
    
    EquipWeapon(CurrentWeaponIndex);
}




void UWeaponComponent::PlayAnimMontage(UAnimMontage *Animation)
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter)
        return;
    OwnerCharacter->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimations()
{
    auto EquipStartNotify = AnimUtils::FindNotifyByClass<UEquipStartAnimNotify>(EquipAnimMontage);
    if (EquipStartNotify)
    {
        EquipStartNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipStart);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("EquipAnimNotify is not set"));
        checkNoEntry();
    }
    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("EquipAnimNotify is not set"));
    }
    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("ReloadAnimNotify is not set"));
            checkNoEntry();
        }
            ReloadFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
        
    }
   
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent*MeshComponent)
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter||MeshComponent!=OwnerCharacter->GetMesh())
        return;

    //if (OwnerCharacter->GetMesh() == MeshComponent)
    //{
        UE_LOG(LogWeaponComponent, Display, TEXT("Equip Finished"));
        EquipInProgress = false;
    //}
}

void UWeaponComponent::OnEquipStart(USkeletalMeshComponent *MeshComponent)
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter || MeshComponent!=OwnerCharacter->GetMesh())
        return;
    //if (OwnerCharacter->GetMesh() == MeshComponent)
    //{
        UE_LOG(LogWeaponComponent, Display, TEXT("Equip Start"));
        EquipInProgress = true;
    //}
}



bool UWeaponComponent::CanFire() const
{
        auto Player = Cast<ABaseCharacter>(CurrentWeapon->GetOwner());

        return CurrentWeapon && !EquipInProgress && !Player->GetIsRunning()&& !ReloadInProgress;
}

bool UWeaponComponent::CanEquip() const
{
        return !EquipInProgress;
}


void UWeaponComponent::Reload()
{
        if (CanEquip() && !ReloadInProgress && CurrentWeapon->HaveAnyAmmo())
        {
        StopFiring();
        PlayAnimMontage(CurrentReloadAnimMontage);
        ReloadInProgress = true;
        }
        else
        {
        UE_LOG(LogWeaponComponent, Error, TEXT("No more ammo to reload"));
        }
}

bool UWeaponComponent::GetWeaponUIData(FWeaponUIData &UIData) const
{
        if (CurrentWeapon)
        {
        UIData = CurrentWeapon->GetUIData();
        return true;
        }
        return false;
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent *MeshComponent)
{
        ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
        if (!OwnerCharacter || MeshComponent != OwnerCharacter->GetMesh())
    return;
        UE_LOG(LogWeaponComponent, Display, TEXT("Reload Finished"));
        CurrentWeapon->Reload();   
    ReloadInProgress = false;
}
bool UWeaponComponent::GetAmmoUIData(FString &AmmoData) const
{
    if (CurrentWeapon)
    {
    AmmoData = CurrentWeapon->GetCurrentAmmo();
    return true;
    }
    return false;
}

bool UWeaponComponent::GetWeaponAmmoUIData(FWeaponUIData &UIData, FString &AmmoData) const
{
    if (CurrentWeapon)
    {
    UIData = CurrentWeapon->GetUIData();
    AmmoData = CurrentWeapon->GetCurrentAmmo();
    return true;
    }
    return false;
}

TSubclassOf<ABaseWeapon> UWeaponComponent::GetWeapon(TSubclassOf<ABaseWeapon> Weapon) const
{
    //int32 foundindex;
    //auto findweapon = Weapons.Find;
    UE_LOG(LogWeaponComponent, Warning, TEXT("Weapon class"));
    const auto CurrentWeaponClass = CurrentWeapon->GetClass();
    if (Weapon == CurrentWeaponClass)
    return CurrentWeaponClass;
    else
    return nullptr;
}


