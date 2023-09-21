// Trying to make a simple game using c++ and a lot of help


#include "Components/BaseAIPerceptionComponent.h"
#include "AIController.h"
#include "ProjectUtils.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"


AActor *UBaseAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor *> PercievedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);
    if (PercievedActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercievedActors);
        if (PercievedActors.Num()==0)
        {
            return nullptr;
        }
        
    }
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
            PercievedActor->FindComponentByClass<UHealthComponent>(); // line ProjectUtils::GetPlayerComponent<UHealthComponent>(PercievedActor) works the same;
        const auto PercievedPawn = Cast<APawn>(PercievedActor);
        const auto AreEnemies = PercievedPawn && ProjectUtils::AreEnemies(Controller, PercievedPawn->Controller);
        if (HealthComponent && !HealthComponent->IsDead()&& AreEnemies) // TODO: check if enemies or not - XdoneX
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
