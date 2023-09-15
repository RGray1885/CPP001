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
        LevelButton->OnHovered.AddDynamic(this, &ULevelIconWidget::OnLevelIconHovered);
        LevelButton->OnUnhovered.AddDynamic(this, &ULevelIconWidget::OnLevelIconUnHovered);
    }
}

void ULevelIconWidget::OnLevelIconClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void ULevelIconWidget::OnLevelIconHovered()
{
    if (IsValid(FrameImage))
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void ULevelIconWidget::OnLevelIconUnHovered()
{
    if (IsValid(FrameImage))
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
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
    if (IsValid(LevelImage))
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}
