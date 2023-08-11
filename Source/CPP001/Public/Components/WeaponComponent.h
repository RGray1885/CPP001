// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ProjectCoreTypes.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

/* USTRUCT(BlueprintType)                   //Moved to ProjectCoreTypes.h
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage *ReloadAnimMontage;
};*/


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP001_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UWeaponComponent();
    bool CanFire() const;


  protected:
    // Called when the game starts
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *EquipAnimMontage;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanEquip() const;
    bool EquipInProgress;
    bool ReloadInProgress;
    
    int32 CurrentWeaponIndex = 0;

    void EquipWeapon(int32 WeaponIndex);
        

    UPROPERTY()
    ABaseWeapon *CurrentWeapon = nullptr; // property for weapon in hand
    UPROPERTY()
    TArray<ABaseWeapon *> Weapons; // array for weapon in possession

  private:
    
    UPROPERTY()
    UAnimMontage *CurrentReloadAnimMontage = nullptr;


    void AttachWeaponToSocket(ABaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
    void SpawnWeapons();
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent*MeshComponent);
    void OnEquipStart(USkeletalMeshComponent *MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent *MeshComponent);
    void OnEmptyClip(ABaseWeapon* AmmoEmptyWeapon);
    
   
    
    bool IsFiring;
   

  
  public:
    virtual void FireWeapon();
    void StopFiring();
    virtual void NextWeapon();
    bool GetIsFiring() const
    {
        return IsFiring;
    }
    void Reload();

    bool GetWeaponUIData(FWeaponUIData &UIData) const;
    bool GetAmmoUIData(FString &AmmoData) const;
    bool GetWeaponAmmoUIData(FWeaponUIData &UIData, FString &AmmoData) const;
    ABaseWeapon* GetWeapon(TSubclassOf<ABaseWeapon> Weapon) const;
  
   
};
