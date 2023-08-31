// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "BaseAIController.generated.h"

/**
 *
 */
class UBaseAIPerceptionComponent;
class URespawnComponent;

UCLASS()
class CPP001_API ABaseAIController : public AAIController
{
    GENERATED_BODY()
  public:
    ABaseAIController();

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UBaseAIPerceptionComponent *AIPerceptionComponent;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    FName FocusOnKeyName = "EnemyActor";
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    URespawnComponent *RespawnComponent;
    virtual void OnPossess(APawn *InPawn) override;
    virtual void Tick(float DeltaTime) override;

    private:
    AActor *GetFocusOnActor() const;
    
};
