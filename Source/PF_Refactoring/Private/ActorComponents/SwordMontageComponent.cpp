#include "ActorComponents/SwordMontageComponent.h"
#include "ActorComponents/StateComponent.h"
#include "ActorComponents/AttributeComponent.h"
#include "Characters/PlayerBase.h"

#include "Utilities.h"


USwordMontageComponent::USwordMontageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USwordMontageComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerBaseRef = Cast<APlayerBase>(GetOwner());

	if (PlayerBaseRef)
	{
		StateComponentRef = PlayerBaseRef->GetStateComponent();
		AttributeComponentRef = PlayerBaseRef->GetAttributeComponent();
		AnimInstanceRef = PlayerBaseRef->GetMesh()->GetAnimInstance();
	}
}

void USwordMontageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool USwordMontageComponent::CheckRef() const
{
	return PlayerBaseRef && AnimInstanceRef && StateComponentRef && AttributeComponentRef;
}

void USwordMontageComponent::PlayEquipMontage()
{
	if (!CheckRef()) return;

	FName sectionName = TEXT("Sword_Drawing");
	if (StateComponentRef->IsArmedState(EArmedState::EAS_Armed))
	{
		sectionName = TEXT("Sword_Sheathing");
	}

	if (EquipMontage)
	{
		AnimInstanceRef->Montage_Play(EquipMontage);
		AnimInstanceRef->Montage_JumpToSection(sectionName, EquipMontage);
	}
}

void USwordMontageComponent::PlayAttackMontage()
{
	if (!CheckRef()) return;
	if (!IdleWalkAttackMontage) return;
	
	if (bEnableCombo)
	{
		bNextCombo = true;
		return;
	}

	if (StateComponentRef->IsActionState(EActionState::EAS_Idle))
	{
		AnimInstanceRef->Montage_Play(IdleWalkAttackMontage, AttributeComponentRef->GetAttackSpeed());
		StateComponentRef->SetActionState(EActionState::EAS_Attacking);
	}
}

void USwordMontageComponent::PlayNextSection(const FName& InSectionName)
{
	if (!CheckRef()) return;
	if (!bNextCombo) return;

	UAnimMontage* currentMontage = AnimInstanceRef->GetCurrentActiveMontage();

	if (currentMontage)
	{
		AnimInstanceRef->Montage_JumpToSection(InSectionName, currentMontage);
		AnimInstanceRef->Montage_SetPlayRate(currentMontage, AttributeComponentRef->GetAttackSpeed());
		StateComponentRef->SetActionState(EActionState::EAS_Attacking);
		bNextCombo = false;
	}
}

void USwordMontageComponent::AttackMontageFinished()
{
	if (!CheckRef()) return;

	bNextCombo = false;
	bEnableCombo = false;

	AnimInstanceRef->Montage_Stop(0.5f);
}

