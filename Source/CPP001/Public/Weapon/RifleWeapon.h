// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */

UCLASS()
class CPP001_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()
  public:
    virtual void StartFire() override;
    virtual void StopFire() override;

  protected:
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
    float BulletSpread = 1.5f;
    UPROPERTY(EditDefaultsonly, Category = "Damage")
    float WeaponRateOfFire = 0.12f;
    UPROPERTY(EditDefaultsonly, Category = "Damage")
    float WeaponFireDelay = 0.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
    bool AutoFireAvailable = true;
  private:
    FTimerHandle ShotTimer;
    bool TriggerPulled;
};
