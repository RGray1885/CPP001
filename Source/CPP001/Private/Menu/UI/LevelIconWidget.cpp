// Trying to make a simple game using c++ and a lot of help


#include "Menu/UI/LevelIconWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void ULevelIconWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (LevelButton)
    {
        LevelButton->OnClicked.AddDynamic(this, &ULevelIconWidget::OnLevelIconClicked);
    }
}

void ULevelIconWidget::OnLevelIconClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void ULevelIconWidget::SetLevelData(const FLevelData &Data)
{
    LevelData = Data;
    if (LevelName)
    {
        LevelName->SetText(FText::FromName(Data.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumbnail);
    }
}

void ULevelIconWidget::SetSelected(bool IsSelected)
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}
