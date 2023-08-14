// Trying to make a simple game using c++ and a lot of help


#include "AI/Services/FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ProjectUtils.h"
#include "Components/BaseAIPerceptionComponent.h"

UFindEnemyService::UFindEnemyService()
{
    NodeName = "FindEnemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{

    UE_LOG(LogTemp, Display, TEXT("FindEnemy"));
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Controller->FindComponentByClass<UBaseAIPerceptionComponent>();
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
}
