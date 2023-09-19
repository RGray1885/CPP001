// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ProjectCoreTypes.h"
#include "HealthComponent.generated.h"


class UCameraShakeBase;
class UPhysicalMaterial;

//DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);            //Moved to ProjectCoreTypes.h
//DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

//DECLARE_MULTICAST_DELEGATE(FOnDamageTaken);

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
    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercentage() const
    {
        return Health / MaxHealth;
    }

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;
    FOnDamageTaken OnDamageTaken;

    UFUNCTION()
  void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController * InstigatedBy,
                                                         FVector HitLocation, class UPrimitiveComponent *
                                                         FHitComponent, FName BoneName, FVector ShotFromDirection,
                                                         const class UDamageType * DamageType, AActor * DamageCauser);
    UFUNCTION()
  void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, 
                                                         const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

  protected:
    // Called when the game starts
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Param",
              meta = (ClampMin = "0.0", ClampMax = "999.0"))
    float MaxHealth = 100;
    UPROPERTY(VisibleAnywhere, BlueprintreadWrite, Category = "Heal")
    bool bShouldHeal = false;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "Heal", meta = (ClampMin = "0.01", ClampMax = "1.0"))
    float HealUpdateTime = 0.1;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "Heal", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    float HealDelay = 1.0;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "Heal", meta = (ClampMin = "0.1", ClampMax = "10.0"))
    float HealModifier = 1.0;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShakeEffect;
    UPROPERTY(EditDefaultsOnly, BlueprintreadWrite, Category = "Health")
    TMap<UPhysicalMaterial *,float> DamageModifier;





    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

    //void DepleteHealth(float Amount);

    bool ShouldHeal() const
    {
        return bShouldHeal;
    }
    void HealFromMedkit(float HealAmount);

  private:
    float Health = 0;
    FTimerHandle HealTimer;

    UFUNCTION()
    void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                         class AController *InstigatedBy, AActor *DamageCauser);
    UFUNCTION()
    void OnHeal();
    void SetHealth(float NewHealth);

    void PlayCameraShake();

    void Killed(AController*KillerController);
    void ApplyDamage(float Damage, AController *InstigatedBy);
    float GetPointDamageModifier(AActor *DamagedActor, const FName &BoneName);
};
