// Trying to make a simple game using c++ and a lot of help


#include "Components/BaseCharMoveComponent.h"
#include "Player/BaseCharacter.h"


float UBaseCharMoveComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ABaseCharacter *Player = Cast<ABaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed*RunModifier: MaxSpeed;
}