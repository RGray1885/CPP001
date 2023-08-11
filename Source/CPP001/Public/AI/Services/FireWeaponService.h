// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FireWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API UFireWeaponService : public UBTService
{
	GENERATED_BODY()


		public:
    UFireWeaponService();

	protected:
    UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};



