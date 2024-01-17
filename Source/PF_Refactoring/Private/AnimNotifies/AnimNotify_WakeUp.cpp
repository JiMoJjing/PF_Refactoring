#include "AnimNotifies/AnimNotify_WakeUp.h"
#include "Characters/CharacterBase.h"


FString UAnimNotify_WakeUp::GetNotifyName_Implementation() const
{
	return FString(TEXT("WakeUp"));
}

void UAnimNotify_WakeUp::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ACharacterBase* characterBaseRef = Cast<ACharacterBase>(MeshComp->GetOwner());

	if (characterBaseRef)
	{
		characterBaseRef->WakeUp();
	}
}
