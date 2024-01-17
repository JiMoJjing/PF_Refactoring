#include "Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "ActorComponents/MontageComponent.h"
#include "ActorComponents/AttributeComponent.h"

#include "Utilities.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionProfileName(TEXT("Custom"));
	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::GetHit_Implementation(const FVector& ImpactPoint, float Strength, AActor* HitActor)
{
	if (Strength == 100.f)
	{
		HitNormalReact(HitActor->GetActorLocation());
	}
	else if (Strength == 200.f)
	{
		HitMiddleReact(HitActor->GetActorLocation());
	}
	else if (Strength == 300.f)
	{
		HitHeavyReact(HitActor->GetActorLocation());
	}
}

void ACharacterBase::HitNormalReact(const FVector& ImpactPoint)
{
	FName sectionName;
	GetDirectionalSectionName(ImpactPoint, sectionName);
	if (MontageComponent)
	{
		MontageComponent->PlayHitNormalMontage(sectionName);
	}
}

void ACharacterBase::HitMiddleReact(const FVector& ImpactPoint)
{
	FName sectionName;
	GetDirectionalSectionName(ImpactPoint, sectionName);
	if (MontageComponent)
	{
		MontageComponent->PlayHitMiddleMontage(sectionName);
	}
}

void ACharacterBase::HitHeavyReact(const FVector& ImpactPoint)
{
	const FVector actorLocation = GetActorLocation();
	const FVector impactPointXY = FVector(ImpactPoint.X, ImpactPoint.Y, actorLocation.Z);

	const FVector toHitVector = (impactPointXY - actorLocation).GetSafeNormal();

	SetActorRotation(toHitVector.Rotation());
	
	if (MontageComponent)
	{
		MontageComponent->PlayHitHeavyMontage();
	}
}

void ACharacterBase::GetDirectionalSectionName(const FVector& ImpactPoint, FName& SectionName)
{
	const FVector actorLocation = GetActorLocation();
	const FVector impactPointXY = FVector(ImpactPoint.X, ImpactPoint.Y, actorLocation.Z);

	const FVector toHitVector = (impactPointXY - actorLocation).GetSafeNormal();

	const FVector forwardVector = GetActorForwardVector();
	const FVector rightVector = GetActorRightVector();

	double theta = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(forwardVector, toHitVector)));
	const double dotRight = FVector::DotProduct(rightVector, toHitVector);

	if (dotRight < 0.f)
	{
		theta *= -1;
	}

	SectionName = TEXT("FromBack");

	if (theta >= -45.f && theta < 45.f)
	{
		SectionName = TEXT("FromFront");
	}
	else if (theta >= 45.f && theta < 135.f)
	{
		SectionName = TEXT("FromRight");
	}
	else if (theta < -45.f && theta >= -135.f)
	{
		SectionName = TEXT("FromLeft");
	}
}

void ACharacterBase::WakeUp()
{
	if (MontageComponent)
	{
		MontageComponent->PlayWakeUpMontage();
	}
}

void ACharacterBase::ReceiveDamage(float InDamage)
{
	if (AttributeComponent)
	{
		AttributeComponent->ReceiveDamage(InDamage);
	}
}
	