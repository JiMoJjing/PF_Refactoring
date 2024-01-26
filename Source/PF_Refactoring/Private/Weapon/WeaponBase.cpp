#include "Weapon/WeaponBase.h"

#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

#include "Utilities.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWeaponBase::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules transformRules(EAttachmentRule::KeepRelative, true);
	Mesh->AttachToComponent(InParent, transformRules, InSocketName);
}


void AWeaponBase::AttackFinished()
{
	
}
