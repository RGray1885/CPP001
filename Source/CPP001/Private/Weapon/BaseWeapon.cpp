// Trying to make a simple game using c++ and a lot of help


#include "Weapon/BaseWeapon.h"
<<<<<<< Updated upstream
=======
#include "Components/SkeletalMeshComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon,All,All);
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
=======
void ABaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
}

>>>>>>> Stashed changes
// Called every frame
/* void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

<<<<<<< Updated upstream
}*/

=======
}*/
>>>>>>> Stashed changes
