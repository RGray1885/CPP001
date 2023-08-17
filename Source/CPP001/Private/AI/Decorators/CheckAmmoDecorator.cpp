// Trying to make a simple game using c++ and a lot of help


#include "AI/Decorators/CheckAmmoDecorator.h"
#include "AIController.h"
#include "Components/AIWeaponComponent.h"


UCheckAmmoDecorator::UCheckAmmoDecorator()
{
    NodeName = "Check Ammo";
}
bool UCheckAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    //if (!WeaponType)
      //  return false;
    
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto Component = Controller->GetPawn()->FindComponentByClass<UAIWeaponComponent>();
    if (!Component)
        return false;
    else
        return Component->CheckAmmunition(WeaponType);
}