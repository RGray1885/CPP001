// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileRocket.generated.h"

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

public:	
	

};
