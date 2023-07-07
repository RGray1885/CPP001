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
    auto Player = Cast<ABaseCharacter> (CurrentWeapon->GetOwner()); //to prevent fire
    if (!Player->GetIsRunning())                                    //during sprint
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
    if (!Weapon || !SceneComponent)                                                     //stop if either parameter is invalid
    return;
    FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);     //set attachment transform rules
    Weapon->AttachToComponent(SceneComponent, AttachmentRule, SocketName);              //attach weapon to socket
}
void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner()); // the same as in SpawnWeapons method
    if (!OwnerCharacter||WeaponClasses.IsEmpty())                           
    return;
    if (CurrentWeapon)                                                                      //if current weapon is valid
    {
    AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName); //attach to another socket (on back by default)
    }
    CurrentWeapon = Weapons[WeaponIndex];                                                   //get new weapon from array
    AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponEquipSocketName);  //attach new weapon to hands socket
}

void UWeaponComponent::SpawnWeapons()                                                       //spawning weapon
{
    ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());                             //Get component's owner->cast to ACharacterClass->promote to var OwnerCharacter of class ACharacter
    if (!OwnerCharacter||!GetWorld()||WeaponClasses.IsEmpty())                             //don't spawn if owner or world is invalid, or weapon classes array is empty
        return;
    for (auto WeaponClass : WeaponClasses)                                                 //spawn WeaponClasses array elements
    {
    auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);                         //spawn actor of class ABaseWeapon
        if (!Weapon)
            continue;
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
    if (!CurrentWeapon)                                                //Cycle if CurrentWeapon is Valid
        return;
    StopFiring();                                                      //Prevent weapon from firing during switching
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();     
    
    EquipWeapon(CurrentWeaponIndex);
}


