#include "Characters/PlayerBaseAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Characters/PlayerBase.h"
#include "ActorComponents/StateComponent.h"

void UPlayerBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PlayerBaseRef = Cast<APlayerBase>(TryGetPawnOwner());
	if (PlayerBaseRef)
	{
		MovementComponentRef = PlayerBaseRef->GetCharacterMovement();
		StateComponentRef = PlayerBaseRef->GetStateComponent();
	}
	if (StateComponentRef)
	{
		StateComponentRef->OnArmedStateChanged.AddDynamic(this, &UPlayerBaseAnimInstance::ArmedStateChanged);
	}
}

void UPlayerBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (PlayerBaseRef == nullptr) return;
	if (MovementComponentRef == nullptr) return;
	if (StateComponentRef == nullptr) return;

	Velocity = MovementComponentRef->Velocity;
	GroundSpeed = Velocity.Size2D();

	const FRotator controlRotation = PlayerBaseRef->GetControlRotation();
	const FRotator actorRotation = PlayerBaseRef->GetActorRotation();

	const FRotator rotation = UKismetMathLibrary::NormalizedDeltaRotator(controlRotation, actorRotation);
	Yaw = rotation.Yaw;
	Pitch = rotation.Pitch;

	/*FVector forwardVector = PlayerBaseRef->GetActorForwardVector();
	FVector rightVector = PlayerBaseRef->GetActorRightVector();
	FVector normalizedVel = Velocity.GetSafeNormal2D();

	float forwardCos = FVector::DotProduct(normalizedVel, forwardVector);
	float forwardTheta = FMath::RadiansToDegrees(FMath::Acos(forwardCos));

	float rightCos = FVector::DotProduct(normalizedVel, rightVector);
	if (rightCos < 0.f)
	{
		forwardTheta *= -1;
	}*/

	MoveDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, actorRotation);

	bMoving = (MovementComponentRef->GetCurrentAcceleration() != FVector::ZeroVector) && (GroundSpeed > 3.f);
	IsFalling = MovementComponentRef->IsFalling();
}

void UPlayerBaseAnimInstance::ArmedStateChanged(EArmedState InArmedState)
{
	ArmedState = InArmedState;
}
