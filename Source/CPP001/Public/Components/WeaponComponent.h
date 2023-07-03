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
    UPROPERTY()
    ABaseWeapon *CurrentWeapon = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachmentPointName = "WeaponSocket";
    virtual void BeginPlay() override;

  
  public:
    void FireWeapon();
    void SpawnWeapon();
    void RemoveWeapon(float LifeSpanOnDeath);
};
