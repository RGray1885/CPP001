// Trying to make a simple game using c++ and a lot of help


#include "UI/PauseWidget.h"
#include "GameFramework/GamemodeBase.h"
#include "Components/Button.h"

bool UPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClearPause);
    }
    return InitStatus;
}

void UPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;
    GetWorld()->GetAuthGameMode()->ClearPause();
}
