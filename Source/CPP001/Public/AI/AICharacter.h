// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
		public:
    AAICharacter(const FObjectInitializer &ObjInit);
};
