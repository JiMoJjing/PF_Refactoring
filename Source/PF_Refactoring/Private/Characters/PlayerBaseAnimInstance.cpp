#include "Characters/PlayerBaseAnimInstance.h"
#include "GameFramework/Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
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

	FRotator controlRotation = PlayerBaseRef->GetControlRotation();
	FRotator actorRotation = PlayerBaseRef->GetActorRotation();

	FRotator rotation = UKismetMathLibrary::NormalizedDeltaRotator(controlRotation, actorRotation);
	Yaw = rotation.Yaw;
	Pitch = rotation.Pitch;

	//float targetDirection = CalculateDirection(PlayerBaseRef->GetVelocity(), FRotator(0.f, controlRotation.Yaw, 0.f));
	//float targetDirection = CalculateDirection(PlayerBaseRef->GetVelocity(), actorRotation);
	//MoveDirection = FMath::FInterpTo(MoveDirection, targetDirection, DeltaSeconds, InterpSpeed);
	MoveDirection = CalculateDirection(PlayerBaseRef->GetVelocity(), actorRotation);

	bMoving = (MovementComponentRef->GetCurrentAcceleration() != FVector::ZeroVector) && (GroundSpeed > 3.f);
	IsFalling = MovementComponentRef->IsFalling();
}

void UPlayerBaseAnimInstance::ArmedStateChanged(EArmedState InArmedState)
{
	ArmedState = InArmedState;
}
