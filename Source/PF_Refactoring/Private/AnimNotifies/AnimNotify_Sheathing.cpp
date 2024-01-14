#include "AnimNotifies/AnimNotify_Sheathing.h"
#include "Characters/PlayerBase.h"
#include "Weapon/WeaponBase.h"

FString UAnimNotify_Sheathing::GetNotifyName_Implementation() const
{
	return FString(TEXT("Sheathing"));
}

void UAnimNotify_Sheathing::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		AWeaponBase* weaponBaseRef = playerBaseRef->GetEquippedWeapon();
		playerBaseRef->Disarm();
		if (weaponBaseRef)
		{
			weaponBaseRef->AttachMeshToSocket(playerBaseRef->GetMesh(), SocketName);
		}
	}
}
