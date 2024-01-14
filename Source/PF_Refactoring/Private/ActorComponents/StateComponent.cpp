#include "ActorComponents/StateComponent.h"
#include "Characters/PlayerBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponents/AttributeComponent.h"
#include "Utilities.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerBaseRef = Cast<APlayerBase>(GetOwner());
	
	if (PlayerBaseRef)
	{
		PlayerBaseRef->MovementModeChangedDelegate.AddDynamic(this, &UStateComponent::MovementModeChanged);

		PlayerBaseRef->OnMoveEvent().AddUObject(this, &UStateComponent::MovementStateChanged);
		/*PlayerBaseRef->OnMoveEvent().AddLambda([this]()
			{
				if (PlayerBaseRef->GetMovementComponent()->IsFalling())
				{
					SetMovementState(EMovementState::EMS_Jumping);
					return;
				}

				if (!PlayerBaseRef->IsMoving())
				{
					SetMovementState(EMovementState::EMS_Idle);
					return;
				}

				float speed = PlayerBaseRef->GetVelocity().Size2D();
				if (FMath::IsNearlyEqual(speed, PlayerBaseRef->GetMovementComponent()->GetMaxSpeed(), 1.f))
				{
					SetMovementState(EMovementState::EMS_Running);
					return;
				}
				else if (FMath::IsNearlyEqual(speed, 200.f, 50.f))
				{
					SetMovementState(EMovementState::EMS_Walking);
					return;
				}
			});*/
	}
}

void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStateComponent::MovementStateChanged()
{
	// If IsFalling, Set EMovementState Jumping
	if (PlayerBaseRef->GetMovementComponent()->IsFalling())
	{
		SetMovementState(EMovementState::EMS_Jumping);
		return;
	}
	// PlayerBase->bMovePressed is false, Set EMovementState Idle
	if (PlayerBaseRef->IsMovePressed() == false)
	{
		SetMovementState(EMovementState::EMS_Idle);
		return;
	}
	// Get speed by velocity for character is running or walking
	float speed = PlayerBaseRef->GetVelocity().Size2D();
	
	// Get runspeed or walkspeed from AttributeComponent for check running or walking
	if (PlayerBaseRef->GetAttributeComponent() == nullptr) return;

	if (PlayerBaseRef->GetCharacterMovement()->GetMaxSpeed() == PlayerBaseRef->GetAttributeComponent()->GetRunSpeed())
	{
		SetMovementState(EMovementState::EMS_Running);
		return;
	}
	else if (PlayerBaseRef->GetCharacterMovement()->GetMaxSpeed() == PlayerBaseRef->GetAttributeComponent()->GetWalkSpeed())
	{
		SetMovementState(EMovementState::EMS_Walking);
		return;
	}
}

void UStateComponent::MovementModeChanged(ACharacter* InCharacter, EMovementMode InPrevMovementMode, uint8 InPrevCustomMovementMode)
{
	//EMovementMode variable from CharacterMovementComponent
	EMovementMode newMovementMode = InCharacter->GetCharacterMovement()->MovementMode;

	switch (newMovementMode)
	{
	case MOVE_None: break;
	case MOVE_Walking: 
	{
		MovementStateChanged();
	};
	break;
	case MOVE_NavWalking: break;
	case MOVE_Falling:
	{
		MovementStateChanged();
	};
	break;
	case MOVE_Swimming: break;
	case MOVE_Flying: break;
	case MOVE_Custom: break;
	case MOVE_MAX: break;
	default: break;
	}
}

void UStateComponent::SetMovementState(EMovementState InState)
{
	MovementState = InState;
}

void UStateComponent::SetActionState(EActionState InActionState)
{
	ActionState = InActionState;
}

void UStateComponent::SetArmedState(EArmedState InArmedState)
{
	ArmedState = InArmedState;
	if (OnArmedStateChanged.IsBound())
	{
		OnArmedStateChanged.Broadcast(ArmedState);
	}
}

bool UStateComponent::CanJump() const
{
	return IsActionState(EActionState::EAS_Idle);
}

bool UStateComponent::CanAttack() const
{
	return IsArmedState(EArmedState::EAS_Armed);
}

void UStateComponent::AttackStateFinished()
{
	if (GetActionState() < EActionState::EAS_Hitted)
	{
		SetActionState(EActionState::EAS_Idle);
		MovementStateChanged();
	}
}
