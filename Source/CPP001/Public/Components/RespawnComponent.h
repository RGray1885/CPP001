// Trying to make a simple game using c++ and a lot of help

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP001_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URespawnComponent();

	void Respawn(int32 RespawnTime);
    
	int32 GetRespawnCountdown() const
    {
        return RespawnCountdown;
    }
    bool IsRespawnInProgress() const;

  private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountdown=0;


	void RespawnTimerUpdate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
