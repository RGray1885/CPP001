// Trying to make a simple game using c++ and a lot of help


#include "Components/RespawnComponent.h"
#include "ShooterGameModeBase.h"

// Sets default values for this component's properties
URespawnComponent::URespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void URespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld())
        return;
    RespawnCountdown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &URespawnComponent::RespawnTimerUpdate, 1.0f,
                                           true);
}


void URespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountdown == 0)
	{
        if (!GetWorld())
            return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);


		const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));

	}
}

// Called when the game starts
void URespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

