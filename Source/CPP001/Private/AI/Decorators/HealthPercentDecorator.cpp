// Trying to make a simple game using c++ and a lot of help


#include "AI/Decorators/HealthPercentDecorator.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

UHealthPercentDecorator::UHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool UHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
    return false;

    const auto HealthComponent = Controller->GetPawn()->FindComponentByClass<UHealthComponent>();
    if (!HealthComponent || HealthComponent->IsDead())
    return false;

    return HealthComponent->GetHealthPercentage() <= HealthPercent;
}
