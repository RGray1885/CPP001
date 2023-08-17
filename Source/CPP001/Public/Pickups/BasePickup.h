// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class URotatingMovementComponent;

UCLASS()
class CPP001_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    UStaticMeshComponent *StaticMeshComponent;
    //UPROPERTY(VisibleAnywhere, Category = "Pickup")
    //URotatingMovementComponent *RotatingMovementComponent;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime=5.0f;
    float RotationYaw = 0.0f;
    FTimerHandle RespawnTimerHandle;
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    //bool CoulBeTakenTest = true;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override; 

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  bool CouldBeTaken() const;

private:
    virtual bool GivePickupTo(APawn *PlayerPawn);
    void PickupTaken();
	void RespawnPickup();
    void GenerateRotationYaw();
};
