// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupVisibility.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API UEnvQueryTest_PickupVisibility : public UEnvQueryTest
{
	GENERATED_BODY()

		public:
    UEnvQueryTest_PickupVisibility(const FObjectInitializer &ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance &QueryInstance) const override;
	
};
