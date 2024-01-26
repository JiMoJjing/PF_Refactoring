#include "AnimNotifies/AnimNotify_JumpToSection.h"
#include "Characters/PlayerSword.h"
#include "ActorComponents/SwordMontageComponent.h"

FString UAnimNotify_JumpToSection::GetNotifyName_Implementation() const
{
	return FString(TEXT("JumpToSection"));
}

void UAnimNotify_JumpToSection::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerSword* playerSwordRef = Cast<APlayerSword>(MeshComp->GetOwner());

	if (playerSwordRef)
	{
		USwordMontageComponent* swordMontageComponentRef = playerSwordRef->GetSwordMontageComponent();
		if (swordMontageComponentRef)
		{
			swordMontageComponentRef->PlayNextSection(SectionName);
		}
	}
}
