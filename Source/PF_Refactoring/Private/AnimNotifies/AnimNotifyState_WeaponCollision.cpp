#include "AnimNotifies/AnimNotifyState_WeaponCollision.h"
#include "Characters/PlayerBase.h"
#include "Weapon/WeaponBase.h"

FString UAnimNotifyState_WeaponCollision::GetNotifyName_Implementation() const
{
	return FString(TEXT("WeaponCollision"));
}

void UAnimNotifyState_WeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		AWeaponBase* weaponBaseRef = playerBaseRef->GetEquippedWeapon();
		if (weaponBaseRef)
		{
			weaponBaseRef->SetBoxCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
}

void UAnimNotifyState_WeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		AWeaponBase* weaponBaseRef = playerBaseRef->GetEquippedWeapon();
		if (weaponBaseRef)
		{
			weaponBaseRef->SetBoxCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}
