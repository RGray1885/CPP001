// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "LauncherWeapon.generated.h"

/**
 * 
 */
class AProjectileRocket;
UCLASS()
class CPP001_API ALauncherWeapon : public ABaseWeapon
{
    GENERATED_BODY()
  
        public:
    virtual void StartFire() override;

        protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AProjectileRocket> ProjectileClass;
    virtual void MakeShot() override;

};
