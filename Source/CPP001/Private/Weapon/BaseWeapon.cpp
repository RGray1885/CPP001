// Trying to make a simple game using c++ and a lot of help


#include "Weapon/BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
/* void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

