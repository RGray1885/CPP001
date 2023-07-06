// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileRocket.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
UCLASS()
class CPP001_API AProjectileRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileRocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent *CollisionComponent;
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon") 
	UProjectileMovementComponent *ProjectileMovementComponent;

public:	
	void SetShotDirection(FVector Direction){ShotDirection = Direction;}
    void SetDamageRadius(float Radius)
    {
        DamageRadius = Radius;
    }
    void SetDamageAmount(float DamageAmount)
    {
       DamageToDeal = DamageAmount;
    }
    void SetDoFullDamage(bool FullDamage)
    {
       DoFullDamage = FullDamage;
    }
    void SetProjectileLifeTime(float ProjectileLifeTime)
    {
       ProjectileLifeSpan = ProjectileLifeTime;
    }

	private:
    FVector ShotDirection;
      float DamageRadius;
    float DamageToDeal;
      bool DoFullDamage;
    float ProjectileLifeSpan;
      UFUNCTION()
      void OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                           FVector NormalImpulse, const FHitResult &Hit);
      AController *GetController() const;
};
