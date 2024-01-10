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
	if (PlayerBaseRef->GetMovementComponent()->IsFalling())
	{
		SetMovementState(EMovementState::EMS_Jumping);
		return;
	}

	if (PlayerBaseRef->IsMovePressed() == false)
	{
		SetMovementState(EMovementState::EMS_Idle);
		return;
	}

	float speed = PlayerBaseRef->GetVelocity().Size2D();

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