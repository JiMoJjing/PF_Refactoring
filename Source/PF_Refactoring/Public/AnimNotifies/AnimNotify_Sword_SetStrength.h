#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Weapon/StrengthEnum.h"
#include "AnimNotify_Sword_SetStrength.generated.h"


UCLASS()
class PF_REFACTORING_API UAnimNotify_Sword_SetStrength : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStrengthType StrengthType = EStrengthType::EST_Normal;
};
