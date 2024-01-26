#include "AnimNotifies/AnimNotify_Sword_SetStrength.h"
#include "Characters/PlayerBase.h"
#include "Weapon/WeaponSword.h"

FString UAnimNotify_Sword_SetStrength::GetNotifyName_Implementation() const
{
	return FString(TEXT("Sword_SetStrength"));
}

void UAnimNotify_Sword_SetStrength::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		AWeaponSword* weaponSwordRef = Cast<AWeaponSword>(playerBaseRef->GetEquippedWeapon());
		if (weaponSwordRef)
		{
			switch (StrengthType)
			{
			case EStrengthType::EST_None:
				weaponSwordRef->SetStrengthNormal();
				break;
			case EStrengthType::EST_Normal:
				weaponSwordRef->SetStrengthNormal();
				break;
			case EStrengthType::EST_Middle:
				weaponSwordRef->SetStrengthMiddle();
				break;
			case EStrengthType::EST_Heavy:
				weaponSwordRef->SetStrengthHeavy();
				break;
			default:
				break;
			}
		}
	}
}
