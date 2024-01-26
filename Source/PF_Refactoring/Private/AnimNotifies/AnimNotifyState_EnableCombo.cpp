#include "AnimNotifies/AnimNotifyState_EnableCombo.h"
#include "Characters/PlayerSword.h"
#include "ActorComponents/SwordMontageComponent.h"

FString UAnimNotifyState_EnableCombo::GetNotifyName_Implementation() const
{
	return FString(TEXT("EnableCombo"));
}

void UAnimNotifyState_EnableCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	APlayerSword* playerSwordRef = Cast<APlayerSword>(MeshComp->GetOwner());

	if (playerSwordRef)
	{
		USwordMontageComponent* swordMontageComponentRef = playerSwordRef->GetSwordMontageComponent();
		if (swordMontageComponentRef)
		{
			swordMontageComponentRef->SetEnableCombo(true);
		}
	}
}

void UAnimNotifyState_EnableCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerSword* playerSwordRef = Cast<APlayerSword>(MeshComp->GetOwner());

	if (playerSwordRef)
	{
		USwordMontageComponent* swordMontageComponentRef = playerSwordRef->GetSwordMontageComponent();
		if (swordMontageComponentRef)
		{
			swordMontageComponentRef->SetEnableCombo(false);
		}
	}
}
