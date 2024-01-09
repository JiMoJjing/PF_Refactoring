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

	OwnerCharacter = Cast<APlayerBase>(GetOwner());
	
	if (OwnerCharacter)
	{
		OwnerCharacter->MovementModeChangedDelegate.AddDynamic(this, &UStateComponent::MovementModeChanged);

		OwnerCharacter->OnMoveEvent().AddUObject(this, &UStateComponent::MovementStateChanged);
		/*OwnerCharacter->OnMoveEvent().AddLambda([this]()
			{
				if (OwnerCharacter->GetMovementComponent()->IsFalling())
				{
					SetMovementState(EMovementState::EMS_Jumping);
					return;
				}

				if (!OwnerCharacter->IsMoving())
				{
					SetMovementState(EMovementState::EMS_Idle);
					return;
				}

				float speed = OwnerCharacter->GetVelocity().Size2D();
				if (FMath::IsNearlyEqual(speed, OwnerCharacter->GetMovementComponent()->GetMaxSpeed(), 1.f))
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
	if (OwnerCharacter->GetMovementComponent()->IsFalling())
	{
		SetMovementState(EMovementState::EMS_Jumping);
		return;
	}

	if (OwnerCharacter->IsMovePressed() == false)
	{
		SetMovementState(EMovementState::EMS_Idle);
		return;
	}

	float speed = OwnerCharacter->GetVelocity().Size2D();

	if (OwnerCharacter->GetAttributeComponent() == nullptr) return;

	if (OwnerCharacter->GetCharacterMovement()->GetMaxSpeed() == OwnerCharacter->GetAttributeComponent()->GetRunSpeed())
	{
		SetMovementState(EMovementState::EMS_Running);
		return;
	}
	else if (OwnerCharacter->GetCharacterMovement()->GetMaxSpeed() == OwnerCharacter->GetAttributeComponent()->GetWalkSpeed())
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