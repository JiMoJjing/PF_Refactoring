#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Sheathing.generated.h"


UCLASS()
class PF_REFACTORING_API UAnimNotify_Sheathing : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SocketName;
};
