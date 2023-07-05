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
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
  bool AutoFireAvailable;
  UPROPERTY(EditDefaultsonly, Category = "Damage")
  float DamagePerHit = 2.0f;
  UPROPERTY(EditDefaultsonly, Category = "Damage")
  float WeaponRateOfFire = 0.12f;


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

public:
  void Fire();
  float GetWeaponRateOfFire(){return WeaponRateOfFire;}
  bool GetAutoFireAvaiability(){return AutoFireAvailable;}


  

protected:
  void MakeShot();
  APlayerController *ABaseWeapon::GetPlayerController() const;
  bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
  FVector GetMuzzleLocation() const;
  bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;
  void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);
  void MakeDamage(const FHitResult& HitResult);
};