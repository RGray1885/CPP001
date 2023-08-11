// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "ChangeWeaponService.generated.h"


/**
 *
 */
UCLASS()
class CPP001_API UChangeWeaponService : public UBTService
{
    GENERATED_BODY()
    UChangeWeaponService();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(ClampMin="0.0",ClampMax="1.0"))
    float ChangeProbability = 0.5f;

  public:
    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
