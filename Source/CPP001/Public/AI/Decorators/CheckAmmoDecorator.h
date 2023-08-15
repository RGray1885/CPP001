// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CheckAmmoDecorator.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API UCheckAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
	public:
    UCheckAmmoDecorator();

	protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
