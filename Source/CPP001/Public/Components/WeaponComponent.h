// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP001_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UWeaponComponent();

  protected:
    // Called when the game starts
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *EquipAnimMontage;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  private:
    UPROPERTY()
    ABaseWeapon *CurrentWeapon = nullptr; //property for weapon in hand
    UPROPERTY()
    TArray<ABaseWeapon *> Weapons; //array for weapon in possession

    int32 CurrentWeaponIndex = 0;

    void AttachWeaponToSocket(ABaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
    void SpawnWeapons();
    void EquipWeapon(int32 WeaponIndex);
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent*MeshComponent);
    void OnEquipStart(USkeletalMeshComponent *MeshComponent);
    bool EquipInProgress;
    bool CanFire() const;
    bool CanEquip() const;
    bool IsFiring;
  
  public:
    void FireWeapon();
    void StopFiring();
    void NextWeapon();
    bool GetIsFiring() const
    {
        return IsFiring;
    }
   
  
   
};
