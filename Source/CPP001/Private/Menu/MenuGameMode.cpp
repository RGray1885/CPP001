// Trying to make a simple game using c++ and a lot of help


#include "Menu/MenuGameMode.h"
#include "Menu/MenuPlayerController.h"
#include "Menu/UI/MenuHUD.h"

AMenuGameMode::AMenuGameMode()
{
    PlayerControllerClass = AMenuPlayerController::StaticClass();
    HUDClass = AMenuHUD::StaticClass();
}
