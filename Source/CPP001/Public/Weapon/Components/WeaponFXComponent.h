// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP001_API UWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponFXComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlayImpactFX(const FHitResult &HitInfo);


	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *DefaultEffect;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;
		
};
