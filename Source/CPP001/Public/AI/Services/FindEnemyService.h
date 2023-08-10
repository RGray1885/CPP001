// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "FindEnemyService.generated.h"

/**
 *
 */
UCLASS()
class CPP001_API UFindEnemyService : public UBTService
{
    GENERATED_BODY()
  public:
    UFindEnemyService();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
