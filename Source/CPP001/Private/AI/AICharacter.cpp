// Trying to make a simple game using c++ and a lot of help


#include "AI/AICharacter.h"
#include "AI/BaseAIController.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass();
}
