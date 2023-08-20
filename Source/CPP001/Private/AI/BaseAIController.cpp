// Trying to make a simple game using c++ and a lot of help


#include "AI/BaseAIController.h"
#include "AI/AICharacter.h"
#include "Components/BaseAIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAIController::ABaseAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UBaseAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);

    bWantsPlayerState = true;
}

void ABaseAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    const auto AICharacter = Cast<AAICharacter>(InPawn);
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }

}

void ABaseAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor(); // AIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);
}

AActor *ABaseAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent())
        return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
