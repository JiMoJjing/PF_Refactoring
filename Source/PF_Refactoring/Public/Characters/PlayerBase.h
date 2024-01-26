#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "InputActionValue.h"
#include "PlayerBase.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UStateComponent;
class UAttributeComponent;
class USwordMontageComponent;
class UTargetComponent;
class AWeapon;

//DECLARE_EVENT(APlayerBase, FMoveEvent);
DECLARE_EVENT_OneParam(APlayerBase, FTestEvent, int32);

UCLASS()
class PF_REFACTORING_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;

protected:
	// Actor Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		UStateComponent* StateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		UTargetComponent* TargetComponent;

	//CharacterBase / AttributeComponent
	
	//CharacterBase / MontageComponent

private:
	// Inputs

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LookAction;

	/** Shift Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LeftShiftAction;

	/** Tab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* TabAction;

	/** Left Mouse Button Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LeftMouseButtonAction;

	/** Right Mouse Button Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* RightMouseButtonAction;

public:
	APlayerBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/* MoveAction */
	// Triggered
	void Move(const FInputActionValue& Value);
	// Completed
	void MoveCompleted();

	/* LookAction */
	// Triggered
	void Look(const FInputActionValue& Value);
	
	/* JumpAction */
	// Triggered
	virtual void Jump() override;
	// Completed
	virtual void StopJumping() override;

	/* LeftShiftAction */
	// Started
	void LeftShiftStarted();
	// Completed
	void LeftShiftCompleted();

	/* TabAction*/
	// Started
	virtual void TabStarted();

	/* LeftMouseButtonAction */
	// Started
	virtual void LeftMouseButtonStarted();

	/* LeftMouseButtonAction */
	void RightMouseButtonStarted();

	void RightMouseButtonCompleted();


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Returns ActorComponents */
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE UStateComponent* GetStateComponent() const { return StateComponent; }

	/** Event
	* MoveEvent
	* RightMouseStartedEvent
	* RightMouseCompletedEvent
	*/
public:
	DECLARE_EVENT(APlayerBase, FMoveEvent);
	FMoveEvent& OnMoveEvent() { return MoveEvent; }

	DECLARE_EVENT(APlayerBase, FRightMouseButtonStarted);
	FRightMouseButtonStarted& OnRightMouseButtonStarted() { return RightMouseButtonStartedEvent; }

	DECLARE_EVENT(APlayerBase, FRightMouseButtonCompleted);
	FRightMouseButtonCompleted& OnRightMouseButtonCompleted() { return RightMouseButtonCompletedEvent; }

private:
	FMoveEvent MoveEvent;

	FRightMouseButtonStarted RightMouseButtonStartedEvent;

	FRightMouseButtonCompleted RightMouseButtonCompletedEvent;



public:
	// True when MoveKeyPressed (W, A, S, D), Use for StateComponent
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsMovePressed() { return bMovePressed; }
private:
	bool bMovePressed = false;
	AActor* LockOnActor;

public:
	// Unarmed <-> Armed, Called from AnimNotify_Drawing, AnimNotify_Sheathing
	UFUNCTION(BlueprintCallable)
		void Arm();
	UFUNCTION(BlueprintCallable)
		void Disarm();

	/** Attack Finished, Called from AnimNotify_Attack_Finished
	* 
	*/
	UFUNCTION(BlueprintCallable)
		virtual void AttackFinished();

protected:
	// Weapon Class for SpawnActorClass
	UPROPERTY(EditAnywhere, category = "Weapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AWeaponBase> WeaponClass;

	// Spawned Weapon
	UPROPERTY()
		AWeaponBase* EquippedWeapon;
public:
	// Weapon Getter
	UFUNCTION(BlueprintCallable, BlueprintPure)
		AWeaponBase* GetEquippedWeapon() { return EquippedWeapon; }

};
