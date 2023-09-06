// Trying to make a simple game using c++ and a lot of help


#include "Menu/MenuPlayerController.h"
#include "GameInstanceBase.h"

void AMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;

}
