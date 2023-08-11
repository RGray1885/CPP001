// Trying to make a simple game using c++ and a lot of help


#include "AI/AICharacter.h"
#include "AI/BaseAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AIWeaponComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponControlComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass();
    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);

    }
}
