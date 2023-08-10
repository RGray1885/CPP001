// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "BaseAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API UBaseAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

		public:
    AActor *GetClosestEnemy() const;
	
};
