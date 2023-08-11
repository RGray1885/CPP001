// Trying to make a simple game using c++ and a lot of help

#include "AI/Services/FireWeaponService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WeaponComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogFireWeapon, All, All);

UFireWeaponService::UFireWeaponService()
{
    NodeName = "Fire Weapon";
}

void UFireWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<UWeaponComponent>();
        if (WeaponComponent)
        {
            if (HasAim&&WeaponComponent->CanFire())
            {
                WeaponComponent->FireWeapon();
                UE_LOG(LogFireWeapon, Warning, TEXT("Firing"));
            }
            else
            {
                WeaponComponent->StopFiring();
                UE_LOG(LogFireWeapon, Warning, TEXT("Firing stopped"));
            }
            //HasAim ? WeaponComponent->FireWeapon() : WeaponComponent->StopFiring();

        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
