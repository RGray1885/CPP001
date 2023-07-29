#pragma once
#include "ProjectCoreTypes.generated.h"

//weapon
class ABaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature,ABaseWeapon*);

USTRUCT(BlueprintType)
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
};
//weaponcomponent
USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage *ReloadAnimMontage;
};
//healthcomponent
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

//weaponUI
USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D *MainIcon;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D *CrosshairIcon;
};
USTRUCT(BlueprintType)
struct FAmmoPickupData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    TSubclassOf<ABaseWeapon> WeaponClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta=(ClampMin="1.0",ClampMax="45.0"))
    int32 Amount;
};