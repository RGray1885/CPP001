// Trying to make a simple game using c++ and a lot of help


#include "Dev/DevDamageZone.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADevDamageZone::ADevDamageZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
	
}

// Called when the game starts or when spawned
void ADevDamageZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADevDamageZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr,
                                        DoFullDamage);

}

