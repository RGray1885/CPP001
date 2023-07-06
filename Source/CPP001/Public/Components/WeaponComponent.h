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

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  private:
    UPROPERTY()
    ABaseWeapon *CurrentWeapon = nullptr;
    UPROPERTY()
    TArray<ABaseWeapon *> Weapons;

    int32 CurrentWeaponIndex = 0;

    void AttachWeaponToSocket(ABaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
    void SpawnWeapons();
    void EquipWeapon(int32 WeaponIndex);
  
  public:
    void FireWeapon();
    void StopFiring();
    void NextWeapon();
    void RemoveWeapon(float LifeSpanOnDeath);

  
   
};
