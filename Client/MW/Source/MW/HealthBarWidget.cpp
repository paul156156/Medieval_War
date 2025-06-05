#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UHealthBarWidget::SetHealthPercent(float Percent)
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetPercent(Percent);
    }
}
