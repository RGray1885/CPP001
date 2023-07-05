// Trying to make a simple game using c++ and a lot of help


#include "Weapon/ProjectileRocket.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectileRocket::AProjectileRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);










}

// Called when the game starts or when spawned
void AProjectileRocket::BeginPlay()
{
	Super::BeginPlay();
	
}


