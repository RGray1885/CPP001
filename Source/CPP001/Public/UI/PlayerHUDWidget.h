// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"


class UWeaponComponent;
class UHealthComponent;
/**
 * 
 */
UCLASS()
class CPP001_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercentage() const;
    //UFUNCTION(BlueprintCallable, Category = "UI")
    //bool GetWeaponUIData(FWeaponUIData &UIData) const;
    //UFUNCTION(BlueprintCallable, Category = "UI")
    //bool GetAmmoUIData(FString &AmmoUIData) const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoUIData(FWeaponUIData &UIData, FString &AmmoUIData) const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;
  protected:
    UWeaponComponent* GetCurrentWeaponComponent()const;
    UHealthComponent* GetHealthComponent() const;
};
