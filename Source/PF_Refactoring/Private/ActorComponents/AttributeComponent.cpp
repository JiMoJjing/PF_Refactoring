#include "ActorComponents/AttributeComponent.h"


UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAttributeComponent::ReceiveDamage(float InDamage)
{
	HP = FMath::Clamp(HP - InDamage, 0.f, MaxHP);
	if (OnHPChanged.IsBound())
	{
		OnHPChanged.Broadcast(MaxHP, HP);
	}
}

