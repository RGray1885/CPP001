// Trying to make a simple game using c++ and a lot of help


#include "UI/PlayerHUDWidget.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "ProjectCoreTypes.h"



float UPlayerHUDWidget::GetHealthPercentage() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return 0.0f;

    const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent)
        return 0.0f;
    return HealthComponent->GetHealthPercentage();

}

/* bool UPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &UIData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (WeaponComponent)
    {
    return WeaponComponent->GetWeaponUIData(UIData);
    }
    else
    return false;

}

bool UPlayerHUDWidget::GetAmmoUIData(FString &AmmoData) const
{
    const auto WeaponComponent=GetWeaponComponent();
    if (WeaponComponent)
    {
    return WeaponComponent->GetAmmoUIData(AmmoData);
    }
    else
    return false;
}
*/
bool UPlayerHUDWidget::GetCurrentWeaponAmmoUIData(FWeaponUIData &UIData, FString &AmmoData) const              // use one function for weapon data to display
{
    const auto WeaponComponent = GetCurrentWeaponComponent();
    if (WeaponComponent)
    {
    return WeaponComponent->GetWeaponAmmoUIData(UIData,AmmoData);
    }
    else
    return false;
}

UWeaponComponent *UPlayerHUDWidget::GetCurrentWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
    return nullptr;

    const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UWeaponComponent>(Component);
    return WeaponComponent;
}




