// Trying to make a simple game using c++ and a lot of help


#include "UI/SpectatorWidget.h"
#include "Components/RespawnComponent.h"

bool USpectatorWidget::GetRespawnTime(int32 &RespawnCountdown) const
{
    const auto RespawnComponent = GetOwningPlayer()->FindComponentByClass<URespawnComponent>();
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
        return false;
       
    RespawnCountdown=RespawnComponent->GetRespawnCountdown();
        return true;
}
