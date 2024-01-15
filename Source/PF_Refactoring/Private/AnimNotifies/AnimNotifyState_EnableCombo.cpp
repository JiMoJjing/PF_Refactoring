#include "AnimNotifies/AnimNotifyState_EnableCombo.h"
#include "Characters/PlayerBase.h"
#include "ActorComponents/SwordMontageComponent.h"

FString UAnimNotifyState_EnableCombo::GetNotifyName_Implementation() const
{
	return FString(TEXT("EnableCombo"));
}

void UAnimNotifyState_EnableCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		USwordMontageComponent* swordMontageComponentRef = playerBaseRef->GetSwordMontageComponent();
		if (swordMontageComponentRef)
		{
			swordMontageComponentRef->SetEnableCombo(true);
		}
	}
}

void UAnimNotifyState_EnableCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		USwordMontageComponent* swordMontageComponentRef = playerBaseRef->GetSwordMontageComponent();
		if (swordMontageComponentRef)
		{
			swordMontageComponentRef->SetEnableCombo(false);
		}
	}
}
