// Trying to make a simple game using c++ and a lot of help


#include "UI/HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!IsValid(HealthBar))
        return;
    
    const ESlateVisibility HealthBarVisibility=(Percent>PercentVisibilityThreshold||FMath::IsNearlyZero(Percent))
                                    ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    HealthBar->SetVisibility(HealthBarVisibility);
    
    const FLinearColor HealthBarColor = (Percent > PercentColorThreshold ? DefaultColor : CritHealthColor);
    HealthBar->SetFillColorAndOpacity(HealthBarColor);
    
    HealthBar->SetPercent(Percent);


}
