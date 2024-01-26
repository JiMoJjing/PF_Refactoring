#include "Characters/PlayerSword.h"

#include "ActorComponents/StateComponent.h"
#include "ActorComponents/SwordMontageComponent.h"
#include "Weapon/WeaponSword.h"

#include "Utilities.h"

APlayerSword::APlayerSword()
{
	PrimaryActorTick.bCanEverTick = true;

	MontageComponent = CreateDefaultSubobject<USwordMontageComponent>(TEXT("SwordMontageComponent"));
}

void APlayerSword::BeginPlay()
{
	Super::BeginPlay();

	if (MontageComponent)
	{
		SwordMontageComponentRef = Cast<USwordMontageComponent>(MontageComponent);
	}

	// Spawn WeaponBase
	if (GetWorld() && WeaponClass)
	{
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.Owner = this;
		actorSpawnParams.Instigator = this;

		FRotator rotation;
		FVector location = FVector::ZeroVector;

		EquippedWeapon = GetWorld()->SpawnActor<AWeaponSword>(WeaponClass, location, rotation, actorSpawnParams);

		if (EquippedWeapon)
		{
			EquippedWeapon->AttachMeshToSocket(GetMesh(), TEXT("Sword_Attach_Pelvis"));
		}
	}
}

void APlayerSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerSword::LeftMouseButtonStarted()
{
	if (StateComponent->IsArmedState(EArmedState::EAS_Armed) && SwordMontageComponentRef)
	{
		SwordMontageComponentRef->PlayAttackMontage();
	}
}

void APlayerSword::TabStarted()
{
	if (SwordMontageComponentRef)
	{
		SwordMontageComponentRef->PlayEquipMontage();
	}
}

void APlayerSword::AttackFinished()
{
	Super::AttackFinished();

	if (SwordMontageComponentRef)
	{
		SwordMontageComponentRef->AttackMontageFinished();
	}
}
