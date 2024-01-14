#include "AnimNotifies/AnimNotify_JumpToSection.h"
#include "Characters/PlayerBase.h"
#include "ActorComponents/MontageComponent.h"

FString UAnimNotify_JumpToSection::GetNotifyName_Implementation() const
{
	return FString(TEXT("JumpToSection"));
}

void UAnimNotify_JumpToSection::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		UMontageComponent* montageComponentRef = playerBaseRef->GetMontageComponent();
		if (montageComponentRef)
		{
			montageComponentRef->PlayNextSection(SectionName);
		}
	}
}
