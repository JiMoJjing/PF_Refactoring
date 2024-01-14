#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Attack_Finished.generated.h"


UCLASS()
class PF_REFACTORING_API UAnimNotify_Attack_Finished : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
