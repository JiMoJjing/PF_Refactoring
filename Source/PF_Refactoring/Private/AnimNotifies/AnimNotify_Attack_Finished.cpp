#include "AnimNotifies/AnimNotify_Attack_Finished.h"
#include "Characters/PlayerBase.h"


FString UAnimNotify_Attack_Finished::GetNotifyName_Implementation() const
{
	return FString(TEXT("Attack_Finished"));
}

void UAnimNotify_Attack_Finished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		playerBaseRef->AttackFinished();
	}
}
