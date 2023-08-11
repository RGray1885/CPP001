// Trying to make a simple game using c++ and a lot of help


#include "AI/Services/ChangeWeaponService.h"
#include "Components/WeaponComponent.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogChangeWeapon, All, All);

UChangeWeaponService::UChangeWeaponService()
{
    NodeName = "Change Weapon";
}




void UChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
        if (Controller)
        {
            const auto Pawn = Controller->GetPawn();

            const auto WeaponComponent = Pawn->FindComponentByClass<UWeaponComponent>();
            if (WeaponComponent&&ChangeProbability>0&&FMath::FRand()<=ChangeProbability)
            {
                WeaponComponent->NextWeapon();
            }
        }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
