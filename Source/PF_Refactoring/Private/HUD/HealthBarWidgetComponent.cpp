#include "HUD/HealthBarWidgetComponent.h"
#include "HUD/HealthBarWidget.h"
#include "ActorComponents/AttributeComponent.h"
#include "Enemy/EnemyBase.h"

void UHealthBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	SetWidgetSpace(EWidgetSpace::Screen);

	AEnemyBase* enemyBaseRef = Cast<AEnemyBase>(GetOwner());
	if (enemyBaseRef)
	{
		UAttributeComponent* attributeComponentRef = enemyBaseRef->GetAttributeComponent();
		if (attributeComponentRef)
		{
			attributeComponentRef->OnHPChanged.AddDynamic(this, &UHealthBarWidgetComponent::HPChanged);
			//attributeComponentRef->OnHPChanged.AddDynamic(HealthBarWidget, &UHealthBarWidget::HPChanged);
			HPChanged(attributeComponentRef->GetMaxHP(), attributeComponentRef->GetHP());
		}
	}
}

void UHealthBarWidgetComponent::HPChanged(float InMaxHP, float InHP)
{
	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UHealthBarWidget>(GetUserWidgetObject());
	}

	if (HealthBarWidget)
	{
		HealthBarWidget->HPChanged(InMaxHP, InHP);
	}
}
