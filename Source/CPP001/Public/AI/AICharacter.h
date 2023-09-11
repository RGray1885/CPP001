// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "AICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class CPP001_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
		public:
    AAICharacter(const FObjectInitializer &ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree *BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

	protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent *HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 1000.f;

	virtual void BeginPlay() override;
    virtual void OnHealthChanged(float Health) override;
    virtual void OnDeath() override;

	private:
    void UpdateHealthWidgetVisibility();
};
