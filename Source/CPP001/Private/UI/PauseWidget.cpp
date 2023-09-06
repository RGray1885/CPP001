// Trying to make a simple game using c++ and a lot of help


#include "UI/PauseWidget.h"
#include "GameFramework/GamemodeBase.h"
#include "Components/Button.h"

void UPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClearPause);
    }
}

void UPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;
    GetWorld()->GetAuthGameMode()->ClearPause();
}
