// Trying to make a simple game using c++ and a lot of help


#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"

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


/* Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

void UWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;
    
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    
    CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
    
    if (!CurrentWeapon) return;
    {
        
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
        CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules,WeaponAttachPointName);
        
    }
}
void UWeaponComponent::Fire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->Fire();
}
