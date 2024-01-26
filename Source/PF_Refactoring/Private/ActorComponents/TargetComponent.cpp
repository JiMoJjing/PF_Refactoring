#include "ActorComponents/TargetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Characters/PlayerBase.h"
#include "ActorComponents/StateComponent.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		PlayerBaseRef = Cast<APlayerBase>(GetOwner());
	}
	if (PlayerBaseRef)
	{
		PlayerBaseRef->OnRightMouseButtonStarted().AddUObject(this, &UTargetComponent::SearchTarget);
		PlayerBaseRef->OnRightMouseButtonCompleted().AddUObject(this, &UTargetComponent::EndTargeting);
	}

}

void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld() == nullptr || TargetActor == nullptr || PlayerBaseRef == nullptr) return;

	const FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(PlayerBaseRef->GetActorLocation(), TargetActor->GetActorLocation());
	FRotator controlRotation = PlayerBaseRef->GetControlRotation();

	controlRotation = FMath::RInterpTo(controlRotation, lookAtRotation, DeltaTime, 5.f);

	PlayerBaseRef->GetController()->SetControlRotation(controlRotation);
}

void UTargetComponent::SearchTarget()
{
	if (PlayerBaseRef == nullptr) return;

	TArray<FHitResult> hitresults;

	SphereTrace(hitresults);

	TArray<AActor*> actors;

	for (FHitResult hitresult : hitresults)
	{
		if (hitresult.GetActor())
		{
			actors.AddUnique(hitresult.GetActor());
		}
	}

	SetTarget(actors);
}

void UTargetComponent::SphereTrace(TArray<FHitResult>& InHitresults)
{
	UWorld* world = GetWorld();

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(GetOwner());

	const FVector playerLocation = PlayerBaseRef->GetActorLocation();

	if (PlayerBaseRef->GetStateComponent()->IsArmedState(EArmedState::EAS_Armed) && world)
	{
		UKismetSystemLibrary::SphereTraceMulti(
			world,
			playerLocation,
			playerLocation + FVector(1.f, 1.f, 1.f),
			TraceRadius,
			ETraceTypeQuery::TraceTypeQuery3,
			false,
			ignoreActors,
			EDrawDebugTrace::ForDuration,
			InHitresults,
			true,
			FLinearColor::Green,
			FLinearColor::Red,
			10.f
		);
	}
}

void UTargetComponent::SetTarget(TArray<AActor*, FDefaultAllocator>& InActors)
{
	for (AActor* actor : InActors)
	{
		if (actor == nullptr) return;

		const FVector playerLocation = PlayerBaseRef->GetActorLocation();
		const FVector playerForwardVecter = PlayerBaseRef->GetActorForwardVector();
		const FVector actorLocation = actor->GetActorLocation();

		float theta = GetTheta(playerLocation, playerForwardVecter, actorLocation);

		if (theta <= InScreenRange)
		{
			if (TargetActor == nullptr)
			{
				TargetActor = actor;
			}
			else
			{
				const FVector targetLocation = TargetActor->GetActorLocation();

				if (theta < GetTheta(playerLocation, playerForwardVecter, targetLocation))
				{
					TargetActor = actor;
				}
			}
		}
	}
}

float UTargetComponent::GetTheta(const FVector& InPlayerLocation, const FVector& InPlayerForwardVector, const FVector& InTargetLocation)
{
	const FVector targetLocation(InTargetLocation.X, InTargetLocation.Y, InPlayerLocation.Z);

	FVector directionVector = targetLocation - InPlayerLocation;
	directionVector.Normalize();

	double theta = FMath::RadiansToDegrees(FMath::Acos(InPlayerForwardVector | directionVector));

	return theta;
}

void UTargetComponent::EndTargeting()
{
	TargetActor = nullptr;
}

