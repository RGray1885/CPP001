// Trying to make a simple game using c++ and a lot of help


#include "Menu/UI/MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstanceBase.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/LevelIconWidget.h"

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
    InitLevelItems();
}

void UMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation *Animation)
{
    if (Animation == HideAnimation)
    {
        const auto GameInstance = GetWorld()->GetGameInstance<UGameInstanceBase>();
        if (!GameInstance)
        {
            return;
        }
        else
        {
            UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevel().LevelName);
        }
    }
    else
    {
        return;
    }
   
}

void UMenuWidget::OnStartGame()
{

     PlayAnimation(HideAnimation);

    

    /* if (GameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Level name is NONE"));
        return;
    }*/
    
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

void UMenuWidget::InitLevelItems()
{
    const auto GameInstance = GetGameInstance();
    if (!GameInstance)
        return;
    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Levels Data must not be Empty!"));

    if (!LevelIconsList)
        return;
    LevelIconsList->ClearChildren();
    for (auto LevelData : GameInstance->GetLevelsData())
    {
        const auto LevelIconWidget = CreateWidget<ULevelIconWidget>(GetWorld(),LevelIconWidgetClass);
        if (!LevelIconWidget)
            continue;

        LevelIconWidget->SetLevelData(LevelData);
        LevelIconWidget->OnLevelSelected.AddUObject(this, &UMenuWidget::OnLevelSelected);
        LevelIconsList->AddChildToHorizontalBox(LevelIconWidget);
        LevelIconWidgets.Add(LevelIconWidget);
    }

    if (GameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(GameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(GameInstance->GetStartupLevel());
    }
}

void UMenuWidget::OnLevelSelected(const FLevelData &Data)
{
    const auto GameInstance = GetGameInstance();
    if (!GameInstance)
        return;
    GameInstance->SetStartupLevel(Data);
    for (auto LevelIconWidget : LevelIconWidgets)
    {
        if (LevelIconWidget)
        {
            const auto IsSelected = Data.LevelName == LevelIconWidget->GetLevelData().LevelName;
            LevelIconWidget->SetSelected(IsSelected);
        }
    }

}

UGameInstanceBase *UMenuWidget::GetGameInstance() const
{
    if (!GetWorld())
    return nullptr;
    return GetWorld()->GetGameInstance<UGameInstanceBase>();
}
