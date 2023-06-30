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
  UPROPERTY(EditDefaultsOnly, Category = "Ammo")
  int32 ClipSize=30;
  UPROPERTY(EditDefaultsOnly, Category = "Ammo")
  int32 CurrentAmmo=30;
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Firing")
  FName MuzzleSocketName = "MuzzleSocket";
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Firing")
  float TraceMaxDistance = 1500.0f;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
public:
  void Fire();

protected:
  void MakeShot();
};
