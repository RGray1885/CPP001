// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharMoveComponent.generated.h"

/**
 * 
 */
UCLASS()
class CPP001_API UBaseCharMoveComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
  public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint", meta= (ClampMin="1.5", ClampMax="10.0"))
    float RunModifier = 2.0f;
	  
	  virtual float GetMaxSpeed() const override;


	
};
