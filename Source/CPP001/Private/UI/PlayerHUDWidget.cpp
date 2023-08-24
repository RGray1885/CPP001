// Trying to make a simple game using c++ and a lot of help


#include "UI/PlayerHUDWidget.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "ProjectCoreTypes.h"
#include "ProjectUtils.h"
#include "Player/BasePlayerState.h"
#include "ShooterGameModeBase.h"



float UPlayerHUDWidget::GetHealthPercentage() const
{
    //const auto Player = GetOwningPlayerPawn();
    //if (!Player)
      //  return 0.0f;

    const auto HealthComponent = ProjectUtils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
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
    const auto WeaponComponent =
        ProjectUtils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn()); // GetCurrentWeaponComponent();
    if (WeaponComponent)
    {
    return WeaponComponent->GetWeaponAmmoUIData(UIData,AmmoData);
    }
    else
    return false;
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent =
        ProjectUtils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn()); // GetHealthComponent();
    return HealthComponent&&!HealthComponent->IsDead();
    //return false;
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller&&Controller->GetStateName()==NAME_Spectating;
}


bool UPlayerHUDWidget::Initialize()
{
    const auto HealthComponent = ProjectUtils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    if (HealthComponent)
    {
    HealthComponent->OnDamageTaken.AddUObject(this, &UPlayerHUDWidget::OnDamageTaken);
    }
    return Super::Initialize();
}

void UPlayerHUDWidget::OnDamageTaken()
{
    OnTakeDamage();
}

/* UWeaponComponent *UPlayerHUDWidget::GetCurrentWeaponComponent() const
{
    //const auto Player = GetOwningPlayerPawn();
    //if (!Player)
    //return nullptr;

    //const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    //const auto WeaponComponent = Cast<UWeaponComponent>(Component);
    const auto WeaponComponent = ProjectUtils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
    if (WeaponComponent)
    {
    return WeaponComponent;
    }
    else
    return nullptr;
    
}

UHealthComponent *UPlayerHUDWidget::GetHealthComponent() const
{
    //const auto Player = GetOwningPlayerPawn();
    
    //if (!Player)
    //return nullptr;
    const auto Component = ProjectUtils::GetPlayerComponent<UHealthComponent>(
        GetOwningPlayerPawn()); // Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (HealthComponent)
    {
    return HealthComponent;
    }
    else
    return nullptr;
}*/

void UPlayerHUDWidget::GetPlayerGameStatistics(int32 &RoundTime, int32 &CurrentRound, int32 &RoundsTotal,
                                               int32 &KillsCount, int32 &DeathsCount) const
{
    const auto PlayerState = Cast<ABasePlayerState>(GetOwningPlayerState());
    const auto CurrentGameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());

    if (!PlayerState||!CurrentGameMode)
    return;

    KillsCount=PlayerState->GetKillCount();
    DeathsCount=PlayerState->GetDeathCount();
    RoundTime = CurrentGameMode->GetRoundTime();
    CurrentRound = CurrentGameMode->GetCurrentRound();
    RoundsTotal = CurrentGameMode->GetTotalRounds();
}



