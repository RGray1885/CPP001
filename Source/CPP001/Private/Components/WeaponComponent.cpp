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
    SpawnWeapon();
	// ...
	
}

void UWeaponComponent::FireWeapon()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->Fire();
}

void UWeaponComponent::SpawnWeapon()
{
    if (!GetWorld())
        return;
	ACharacter *OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter)
        return;

    if (!WeaponClass)
        return;
    CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	if (CurrentWeapon)
	{
        FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);
        CurrentWeapon->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentRule, "WeaponSocket");
        CurrentWeapon->SetOwner(OwnerCharacter);
	}
}


