#include "AnimNotifies/AnimNotify_Sword_SetStrength.h"
#include "Characters/PlayerBase.h"
#include "Weapon/WeaponBase.h"

FString UAnimNotify_Sword_SetStrength::GetNotifyName_Implementation() const
{
	return FString(TEXT("Sword_SetStrength"));
}

void UAnimNotify_Sword_SetStrength::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		AWeaponBase* weaponBaseRef = playerBaseRef->GetEquippedWeapon();
		if (weaponBaseRef)
		{
			switch (StrengthType)
			{
			case EStrengthType::EST_None:
				weaponBaseRef->SetStrengthNormal();
				break;
			case EStrengthType::EST_Normal:
				weaponBaseRef->SetStrengthNormal();
				break;
			case EStrengthType::EST_Middle:
				weaponBaseRef->SetStrengthMiddle();
				break;
			case EStrengthType::EST_Heavy:
				weaponBaseRef->SetStrengthHeavy();
				break;
			default:
				break;
			}
		}
	}
}
