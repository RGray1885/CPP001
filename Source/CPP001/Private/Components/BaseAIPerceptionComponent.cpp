// Trying to make a simple game using c++ and a lot of help


#include "Components/BaseAIPerceptionComponent.h"
#include "AIController.h"
#include "ProjectUtils.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"


AActor *UBaseAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor *> PercievedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);
    if (PercievedActors.Num() == 0)
        return nullptr;
    
    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
        return nullptr;
    
    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float BestDistance = MAX_FLT;
    AActor *BestPawn = nullptr;

    for (const auto PercievedActor : PercievedActors)
    {
        const auto HealthComponent = 
            PercievedActor->FindComponentByClass<UHealthComponent>(); // ProjectUtils::GetPlayerComponent<UHealthComponent>(PercievedActor);
        if (HealthComponent && !HealthComponent->IsDead()) // TODO: check if enemies or not
        {
            const auto CurrentDistance = (PercievedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercievedActor;
            }
        }
    }
    return BestPawn;
}
