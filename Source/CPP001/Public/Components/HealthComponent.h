// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP001_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UHealthComponent();
    float GetHealth() const
    {
        return Health;
    }

  protected:
    // Called when the game starts
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Param",
              meta = (ClampMin = "0.0", ClampMax = "999.0"))
    float MaxHealth = 100;
    virtual void BeginPlay() override;

  public:
    // Called every frame
    /* virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                                    FActorComponentTickFunction *ThisTickFunction)
     override;
    */
    void DepleteHealth(float Amount);
    
  private:
    float Health = 0;
    UFUNCTION()
    void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                               class AController *InstigatedBy, AActor *DamageCauser);
};
