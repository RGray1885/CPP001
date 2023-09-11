// Trying to make a simple game using c++ and a lot of help


#include "AI/AICharacter.h"
#include "AI/BaseAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/HealthBarWidget.h"
#include "Components/HealthComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponControlComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AAIController::StaticClass();
    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);

    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateHealthWidgetVisibility();
}


void AAICharacter::BeginPlay()
{
    Super::BeginPlay();
    check(HealthWidgetComponent);
}

void AAICharacter::OnHealthChanged(float Health)
{
    Super::OnHealthChanged(Health);

    const auto HealthBarWidget = Cast<UHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!IsValid(HealthBarWidget))
        return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercentage());
}

void AAICharacter::OnDeath()
{
    Super::OnDeath();
    WeaponComponent = GetComponentByClass<UAIWeaponComponent>();
    if (WeaponComponent)
    {
    WeaponComponent->StopFiring();
    }

    const auto CurrentController = Cast<AAIController>(Controller);
    if (CurrentController && CurrentController->BrainComponent)
    {
        CurrentController->BrainComponent->Cleanup();
    }

}

void AAICharacter::UpdateHealthWidgetVisibility()
{
    if (!IsValid(GetWorld()) 
        ||!IsValid(GetWorld()->GetFirstPlayerController())
        ||!IsValid(GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()))
    {
        return;
    }
    else
    {
        const FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        const float Distance = FVector::Distance(GetActorLocation(), PlayerLocation);
        HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
    }
}
