// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Components/WeaponComponent.h"
#include "CoreMinimal.h"
#include "AIWeaponComponent.generated.h"


/**
 *
 */
UCLASS()
class CPP001_API UAIWeaponComponent : public UWeaponComponent
{
    GENERATED_BODY()

  public:
    virtual void FireWeapon() override;
    virtual void NextWeapon() override;
};
