// Trying to make a simple game using c++ and a lot of help


#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/DecalComponent.h"


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
    auto ImpactData = DefaultImpactData;

	if (HitInfo.PhysMaterial.IsValid())    //look for shared weak pointers in c++
	{
        const auto PhysMat = HitInfo.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
            ImpactData = ImpactDataMap[PhysMat];
           
		}
	}
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, HitInfo.ImpactPoint,
                                                   HitInfo.ImpactNormal.Rotation());
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, HitInfo.ImpactPoint);

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size,
                                           HitInfo.Location, HitInfo.ImpactNormal.Rotation());
	if (DecalComponent)
	{
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
	
}

