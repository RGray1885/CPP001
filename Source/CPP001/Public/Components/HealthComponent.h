// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ProjectCoreTypes.h"
#include "HealthComponent.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);            //Moved to ProjectCoreTypes.h
//DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

    UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class CPP001_API UHealthComponent
    : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UHealthComponent();
    float GetHealth() const
    {
        return Health;
    }
    UFUNCTION(BlueprintCallable)
    bool IsDead() const
    {
        return Health <= 0;
    }

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

  protected:
    // Called when the game starts
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Param",
              meta = (ClampMin = "0.0", ClampMax = "999.0"))
    float MaxHealth = 100;
    UPROPERTY(VisibleAnywhere, BlueprintreadWrite, Category = "Heal")
    bool bShouldHeal = false;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "Heal", meta = (ClampMin = "0.1", ClampMax = "1.0"))
    float HealUpdateTime = 0.1;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "Heal", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    float HealDelay = 1.0;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "Heal", meta = (ClampMin = "1.0", ClampMax = "3.0"))
    float HealModifier = 1.0;

    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

    //void DepleteHealth(float Amount);

  private:
    float Health = 0;
    FTimerHandle HealTimer;

    UFUNCTION()
    void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                         class AController *InstigatedBy, AActor *DamageCauser);
    UFUNCTION()
    void OnHeal();
    void SetHealth(float NewHealth);
};
