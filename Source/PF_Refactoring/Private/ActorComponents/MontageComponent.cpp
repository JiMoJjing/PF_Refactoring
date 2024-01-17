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

void UMontageComponent::PlayMontage(UAnimMontage* InAnimMontage)
{
	if (AnimInstanceRef && InAnimMontage)
	{
		AnimInstanceRef->Montage_Play(InAnimMontage);
	}
}

void UMontageComponent::PlayHitNormalMontage(const FName& SectionName)
{
	PlayMontageSection(HitNormalMontage, SectionName);
}

void UMontageComponent::PlayHitMiddleMontage(const FName& SectionName)
{
	PlayMontageSection(HitMiddleMontage, SectionName);
}

void UMontageComponent::PlayHitHeavyMontage()
{
	PlayMontage(HitHeavyMontage);
}

void UMontageComponent::PlayWakeUpMontage()
{
	PlayMontage(WakeUpMontage);
}

