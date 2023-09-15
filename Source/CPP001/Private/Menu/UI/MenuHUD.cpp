// Trying to make a simple game using c++ and a lot of help


#include "Menu/UI/MenuHUD.h"
#include "UI/BaseWidget.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UBaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
