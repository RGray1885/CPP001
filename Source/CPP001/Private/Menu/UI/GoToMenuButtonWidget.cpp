// Trying to make a simple game using c++ and a lot of help


#include "Menu/UI/GoToMenuButtonWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceBase.h"

void UGoToMenuButtonWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UGoToMenuButtonWidget::GoToMainMenu);
    }
}

void UGoToMenuButtonWidget::GoToMainMenu()
{
    const auto GameInstance = GetWorld()->GetGameInstance<UGameInstanceBase>();
    UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetMenuLevelName());
}
