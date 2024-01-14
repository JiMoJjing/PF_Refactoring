#include "AnimNotifies/AnimNotify_Drawing.h"
#include "Characters/PlayerBase.h"
#include "Weapon/WeaponBase.h"

FString UAnimNotify_Drawing::GetNotifyName_Implementation() const
{
	return FString(TEXT("Drawing"));
}

void UAnimNotify_Drawing::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	APlayerBase* playerBaseRef = Cast<APlayerBase>(MeshComp->GetOwner());

	if (playerBaseRef)
	{
		AWeaponBase* weaponBaseRef = playerBaseRef->GetEquippedWeapon();
		playerBaseRef->Arm();
		if (weaponBaseRef)
		{
			weaponBaseRef->AttachMeshToSocket(playerBaseRef->GetMesh(), SocketName);
		}
	}
}
