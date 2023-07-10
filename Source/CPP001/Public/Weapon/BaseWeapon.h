// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "!NoReload"))
    int32 ClipSize;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo",meta=(EditCondition="!HasInfiniteAmmo"))
    int32 TotalAmmo;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    bool HasInfiniteAmmo = false;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    bool NoReload = false;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 AmmoPerShotConsumption;

};
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
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
  FName MuzzleSocketName = "MuzzleSocket";
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
  float TraceMaxDistance = 1500.0f;
  UPROPERTY(EditDefaultsonly, Category = "Damage")
  float DamagePerHit = 2.0f;
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
  FAmmoData DefaultAmmo{15, 150, false, false,1};
 
  


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

public:
  virtual void StartFire();
  virtual void StopFire();
  
  

protected:
  virtual void MakeShot();
  virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

  APlayerController *ABaseWeapon::GetPlayerController() const;
  bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
  FVector GetMuzzleLocation() const;
  void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);
  //void AmmoConsumption();
  void ConsumeAmmo();
  bool HaveNoAmmoToShoot() const;
  bool IsClipEmpty() const;
  void ReloadClip();
  void LogAmmo();

private:
  FAmmoData CurrentAmmo;


};


