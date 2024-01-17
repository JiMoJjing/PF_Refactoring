#include "Enemy/EnemyBase.h"
#include "ActorComponents/MontageComponent.h"
#include "ActorComponents/AttributeComponent.h"
#include "HUD/HealthBarWidgetComponent.h"

#include "Blueprint/UserWidget.h"

AEnemyBase::AEnemyBase()
{
	MontageComponent = CreateDefaultSubobject<UMontageComponent>(TEXT("MontageComponent"));
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	HealthBarWidgetComponent = CreateDefaultSubobject<UHealthBarWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
	HealthBarWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	HealthBarWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ReceiveDamage(DamageAmount);

	return DamageAmount;
}

void AEnemyBase::HPChanged(float InHPMax, float InHP)
{
	if (HealthBarWidgetComponent)
	{
		HealthBarWidgetComponent->HPChanged(InHPMax, InHP);
	}
}

void AEnemyBase::ReceiveDamage(float InDamage)
{
	Super::ReceiveDamage(InDamage);

}
