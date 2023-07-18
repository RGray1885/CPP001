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

bool UPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &UIData) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)return false;
    
    const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UWeaponComponent>(Component);
    
    if (WeaponComponent)
    {
    return WeaponComponent->GetWeaponUIData(UIData);
    }
    else
    return false;

}
