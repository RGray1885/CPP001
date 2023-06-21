// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevDamageZone.generated.h"

UCLASS()
class CPP001_API ADevDamageZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevDamageZone();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent *SceneComponent;
    UPROPERTY(EditAnywhere, BlueprintreadWrite)
    FColor SphereColor = FColor::Red;
    UPROPERTY(EditAnywhere, BlueprintreadWrite)
    float Radius = 250.0f;
    UPROPERTY(EditAnywhere, BlueprintreadWrite)
    float Damage = 1.0f;
    UPROPERTY(EditAnywhere, BlueprintreadWrite)
    bool DoFullDamage = true;
    UPROPERTY(EditAnywhere, BlueprintreadWrite)
    TSubclassOf<UDamageType> DamageType;
  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
