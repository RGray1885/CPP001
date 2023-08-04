// Trying to make a simple game using c++ and a lot of help


#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values for this component's properties
UWeaponFXComponent::UWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponFXComponent::PlayImpactFX(const FHitResult &HitInfo)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitInfo.ImpactPoint,
                                                   HitInfo.ImpactNormal.Rotation());
}

