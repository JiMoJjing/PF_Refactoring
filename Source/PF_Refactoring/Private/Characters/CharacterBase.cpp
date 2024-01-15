#include "Characters/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "ActorComponents/MontageComponent.h"

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
	HitReact(HitActor->GetActorLocation(), Strength);
}

void ACharacterBase::HitReact(const FVector& ImpactPoint, float Strength)
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

	FName sectionName = TEXT("FromBack");

	if (theta >= -45.f && theta < 45.f)
	{
		sectionName = TEXT("FromFront");
	}
	else if (theta >= 45.f && theta < 135.f)
	{
		sectionName = TEXT("FromRight");
	}
	else if (theta < -45.f && theta >= -135.f)
	{
		sectionName = TEXT("FromLeft");
	}

	if (MontageComponent)
	{
		MontageComponent->PlayHitMontage(Strength, sectionName);
	}
}
