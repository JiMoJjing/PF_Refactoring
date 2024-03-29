#include "Characters/PlayerBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "ActorComponents/StateComponent.h"
#include "ActorComponents/AttributeComponent.h"
#include "ActorComponents/MontageComponent.h"
#include "ActorComponents/SwordMontageComponent.h"
#include "ActorComponents/TargetComponent.h"

#include "Weapon/WeaponBase.h"
#include "Enemy/EnemyBase.h"

#include "Utilities.h"

APlayerBase::APlayerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	TargetComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetComponent"));
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerBase::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerBase::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerBase::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerBase::MoveCompleted);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerBase::Look);

		//LeftShift
		EnhancedInputComponent->BindAction(LeftShiftAction, ETriggerEvent::Started, this, &APlayerBase::LeftShiftStarted);
		EnhancedInputComponent->BindAction(LeftShiftAction, ETriggerEvent::Completed, this, &APlayerBase::LeftShiftCompleted);

		//Tab
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Started, this, &APlayerBase::TabStarted);

		//LeftMouseButton
		EnhancedInputComponent->BindAction(LeftMouseButtonAction, ETriggerEvent::Started, this, &APlayerBase::LeftMouseButtonStarted);

		//RightMouseButton
		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Started, this, &APlayerBase::RightMouseButtonStarted);
		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Completed, this, &APlayerBase::RightMouseButtonCompleted);
	}
}

void APlayerBase::Move(const FInputActionValue& Value)
{
	if (StateComponent && !StateComponent->IsActionState(EActionState::EAS_Idle)) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
	if (!bMovePressed)
	{
		bMovePressed = true;
	}
	if (MoveEvent.IsBound())
	{
		MoveEvent.Broadcast();
	}
}

void APlayerBase::MoveCompleted()
{
	bMovePressed = false;
	if (MoveEvent.IsBound())
	{
		MoveEvent.Broadcast();
	}
}

void APlayerBase::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerBase::Jump()
{
	if (StateComponent && !StateComponent->CanJump()) return;

	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;
}

void APlayerBase::StopJumping()
{
	bPressedJump = false;
	ResetJumpState();
}

void APlayerBase::LeftShiftStarted()
{
	// Set Running Speed
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void APlayerBase::LeftShiftCompleted()
{
	// Set Walking Speed
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

void APlayerBase::TabStarted()
{

}

void APlayerBase::LeftMouseButtonStarted()
{
	
}

void APlayerBase::RightMouseButtonStarted()
{
	if (RightMouseButtonStartedEvent.IsBound())
	{
		RightMouseButtonStartedEvent.Broadcast();
	}
}


void APlayerBase::RightMouseButtonCompleted()
{
	if (RightMouseButtonCompletedEvent.IsBound())
	{
		RightMouseButtonCompletedEvent.Broadcast();
	}
}

void APlayerBase::Arm()
{
	//
	StateComponent->SetArmedState(EArmedState::EAS_Armed);
	bUseControllerRotationYaw = true;
}

void APlayerBase::Disarm()
{
	StateComponent->SetArmedState(EArmedState::EAS_Unarmed);
	bUseControllerRotationYaw = false;
}

void APlayerBase::AttackFinished()
{
	if (StateComponent)
	{
		StateComponent->AttackStateFinished();
	}
	if (EquippedWeapon)
	{
		EquippedWeapon->AttackFinished();
	}
}
