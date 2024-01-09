#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerBase.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

//DECLARE_EVENT(APlayerBase, FMoveEvent);
DECLARE_EVENT_OneParam(APlayerBase, FTestEvent, int32);

UCLASS()
class PF_REFACTORING_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;
private:
	// Actor Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UStateComponent* StateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		class UAttributeComponent* AttributeComponent;

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

	/** Mouse Left Button Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LeftMouseButtonAction;

	/** Combo Dash Action (WW)*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* DashAction;


public:
	APlayerBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void MoveCompleted();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	virtual void Jump() override;
	virtual void StopJumping() override;

	void LeftShiftPressed();
	void LeftShiftReleased();

	void TabPressed();

	void LeftMouseButtonPressed();

	void Dash();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Returns ActorComponents */
	UFUNCTION()
		FORCEINLINE UStateComponent* GetStateComponent() const { return StateComponent; }
	UFUNCTION()
		FORCEINLINE UAttributeComponent* GetAttributeComponent() const { return AttributeComponent; }

public:
	/** DECLARE_EVENT */
	DECLARE_EVENT(APlayerBase, FMoveEvent);
	FMoveEvent& OnMoveEvent() { return MoveEvent; }
private:
	FMoveEvent MoveEvent;


public:
	/** 현재 움직임 입력이 있는지 체크할 bool */
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsMovePressed() { return bMovePressed; }
private:
	bool bMovePressed = false;

	/** Montages */
private:
	UPROPERTY(EditAnywhere, category = "Montages", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, category = "Montages", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* IdleWalkComboMontage;

	UPROPERTY(EditAnywhere, category = "Montages", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* RunningComboMontage;

	UPROPERTY(EditAnywhere, category = "Montages", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* JumpComboMontage;

	/** Unarmed <-> Armed */
public:
	void PlayEquipMontage(const FName& SectionName);

	UFUNCTION(BlueprintCallable)
		void Arm();
	UFUNCTION(BlueprintCallable)
		void Disarm();

	/** Weapons */
private:
	UPROPERTY(EditAnywhere, category = "Weapon", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AWeaponBase> WeaponClass;
	UPROPERTY()
		class AWeaponBase* EquippedWeapon;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		class AWeaponBase* GetEquippedWeapon() { return EquippedWeapon; }
};
