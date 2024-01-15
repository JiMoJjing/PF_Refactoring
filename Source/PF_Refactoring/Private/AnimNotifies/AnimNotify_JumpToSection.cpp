#include "AnimNotifies/AnimNotify_JumpToSection.h"
#include "Characters/PlayerBase.h"
#include "ActorComponents/SwordMontageComponent.h"

FString UAnimNotify_JumpToSection::GetNotifyName_Implementation() const
{
	return FString(TEXT("JumpToSection"));
}

void UAnimNotify_JumpToSection::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		USwordMontageComponent* swordMontageComponentRef = playerBaseRef->GetSwordMontageComponent();
		if (swordMontageComponentRef)
		{
			swordMontageComponentRef->PlayNextSection(SectionName);
		}
	}
}
