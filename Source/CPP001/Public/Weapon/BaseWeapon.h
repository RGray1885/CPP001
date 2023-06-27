// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
UCLASS()
class CPP001_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent *WeaponMesh;
<<<<<<< Updated upstream
  UPROPERTY(EditDefaultsOnly, Category = "Ammo")
  int32 ClipSize;
  UPROPERTY(EditDefaultsOnly, Category = "Ammo")
  int32 CurrentAmmo;
=======
 
>>>>>>> Stashed changes

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
<<<<<<< Updated upstream
=======
  virtual void Fire();
>>>>>>> Stashed changes

};
