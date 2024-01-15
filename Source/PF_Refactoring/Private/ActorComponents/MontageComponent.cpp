#include "ActorComponents/MontageComponent.h"
#include "Characters/CharacterBase.h"
#include "Components/SkeletalMeshComponent.h"

UMontageComponent::UMontageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterBaseRef = Cast<ACharacterBase>(GetOwner());
	if (CharacterBaseRef)
	{
		AnimInstanceRef = CharacterBaseRef->GetMesh()->GetAnimInstance();
	}
}

void UMontageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMontageComponent::PlayMontageSection(UAnimMontage* InAnimMontage, const FName& SectionName)
{
	if (AnimInstanceRef && InAnimMontage)
	{
		AnimInstanceRef->Montage_Play(InAnimMontage);
		AnimInstanceRef->Montage_JumpToSection(SectionName, InAnimMontage);
	}
}

void UMontageComponent::PlayHitMontage(float InStrength, const FName& SectionName)
{
	if (HitNormalMontage && (InStrength == 100.f))
	{
		PlayMontageSection(HitNormalMontage, SectionName);
	}
	else if (HitMiddleMontage && (InStrength == 200.f))
	{
		PlayMontageSection(HitMiddleMontage, SectionName);
	}
}
