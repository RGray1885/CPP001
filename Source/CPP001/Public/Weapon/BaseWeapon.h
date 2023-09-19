// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectCoreTypes.h"
#include "BaseWeapon.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;
//DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

/* USTRUCT(BlueprintType)                                                                               //Moved to ProjectCoreTypes.h
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "!NoReload"))
    int32 ClipSize;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "!HasInfiniteAmmo"))
    int32 TotalAmmo;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    bool HasInfiniteAmmo = false;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    bool NoReload = false;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 AmmoPerShotConsumption;
};*/
class USkeletalMeshComponent;
UCLASS()
class CPP001_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
  

  public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
  FOnClipEmptySignature OnClipEmpty;

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
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
  FWeaponUIData UIData;
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  UNiagaraSystem *MuzzleFX;
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
  USoundCue *FireSound;
  
 

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

public:
  virtual void StartFire();
  virtual void StopFire();
  
  virtual void Zoom(bool Enabled);
  void Reload();
  bool ShouldReload()
  {
      return IsClipEmpty()||IsClipNotFull();
  }
  bool HaveAnyAmmo()
  {
      return !HaveNoAmmoToShoot()&& CurrentAmmo.TotalAmmo>0;
  }
  FWeaponUIData GetUIData() const
  {
      return UIData;
  }
  FString GetCurrentAmmo() const;
  bool RefillAmmo(int32 Amount);
  bool HaveNoAmmoToShoot() const;
  bool IsClipNotFull() const
  {
      return CurrentAmmo.ClipSize < DefaultAmmo.ClipSize;
  }
  bool IsClipEmpty() const
  {
      return CurrentAmmo.ClipSize == 0;
  }
  

protected:
  virtual void MakeShot();
  virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;


  APlayerController *ABaseWeapon::GetPlayerController() const;
  bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
  FVector GetMuzzleLocation() const;
  void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);
  //void AmmoConsumption();
  void ConsumeAmmo();
  
  void ReloadClip();
  void LogAmmo();
  UNiagaraComponent *SpawnMuzzleFX();

  private:
  FAmmoData CurrentAmmo;


};


