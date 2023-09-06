// Trying to make a simple game using c++ and a lot of help


#include "Menu/UI/MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);


void UMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
    }
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitGame);
    }
}

void UMenuWidget::OnStartGame()
{
    if (!GetWorld())
        return;

    const auto GameInstance = GetWorld()->GetGameInstance<UGameInstanceBase>();
    if (!GameInstance)
        return;

    if (GameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Level name is NONE"));
        return;
    }
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
}

void UMenuWidget::OnQuitGame()
{
    if (!GetWorld())
        return;

    const auto GameInstance = GetWorld()->GetGameInstance<UGameInstanceBase>();
    if (!GameInstance)
        return;

    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
