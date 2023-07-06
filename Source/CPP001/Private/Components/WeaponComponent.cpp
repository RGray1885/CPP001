// Trying to make a simple game using c++ and a lot of help


#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "Player/BaseCharacter.h"

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
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
	// ...
	
}

void UWeaponComponent::FireWeapon()
{
    if (!CurrentWeapon)
        return;
    auto Player = Cast<ABaseCharacter> (CurrentWeapon->GetOwner());
    if (!Player->GetIsRunning())
    CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFiring()
{
    if (!CurrentWeapon)
    return;
    CurrentWeapon->StopFire();
}


void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon *Weapon, USceneComponent *SceneComponent,
                                            const FName &SocketName)
{
    if (!Weapon || !SceneComponent)
    return;
    FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRule, SocketName);
    //Weapon->SetOwner(OwnerCharacter);
}
void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter||WeaponClasses.IsEmpty())
    return;
    if (CurrentWeapon)
    {
    //CurrentWeapon->Detach
    
    AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName);
    }
    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponEquipSocketName);
}

void UWeaponComponent::SpawnWeapons()
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter||!GetWorld()||WeaponClasses.IsEmpty())
        return;
    for (auto WeaponClass : WeaponClasses)
    {
    auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
        if (!Weapon)
            continue;
        Weapon->SetOwner(OwnerCharacter);
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName);
    }
}



void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
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

void UWeaponComponent::NextWeapon()
{
    if (!CurrentWeapon)
        return;
    StopFiring();
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    
    EquipWeapon(CurrentWeaponIndex);
}


