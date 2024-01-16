#include "HUD/HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::HPChanged(float InMaxHP, float InHP)
{
	MaxHP = InMaxHP;
	HP = InHP;

	HealthBar->SetPercent(InHP / InMaxHP);
}
