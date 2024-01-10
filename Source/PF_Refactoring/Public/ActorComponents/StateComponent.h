#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/StateEnums.h"
#include "StateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmedStateChanged, EArmedState, InArmedType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_REFACTORING_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/**
	* EMovementState Getter, Setter, Is
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE EMovementState GetMovementState() const { return MovementState; }

	UFUNCTION(BlueprintCallable)
		void SetMovementState(EMovementState InMovementState);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsMovementState(EMovementState InMovementState) const { return MovementState == InMovementState; }

	/**
	* EActionState Getter, Setter, Is
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE EActionState GetActionState() const { return ActionState; }

	UFUNCTION(BlueprintCallable)
		void SetActionState(EActionState InActionState);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsActionState(EActionState InActionState) const { return ActionState == InActionState; }

	/**
	* EActionState Getter, Setter, Is
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE EArmedState GetArmedState() const { return ArmedState; }

	UFUNCTION(BlueprintCallable)
		void SetArmedState(EArmedState InArmedState);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsArmedState(EArmedState InArmedState) const { return ArmedState == InArmedState; }

	/**
	* PlayerBase - FMoveEvent 바인딩
	* Character->MovementModeChangedDelegate 바인딩
	*/
	UFUNCTION(BlueprintCallable)
		void MovementStateChanged();

	UFUNCTION(BlueprintCallable)
		void MovementModeChanged(ACharacter* InCharacter, EMovementMode InPrevMovementMode, uint8 InPrevCustomMovementMode);

	/**
	* DELEGATE
	*/
	UPROPERTY(BlueprintAssignable)
		FArmedStateChanged OnArmedStateChanged;
private:
	EMovementState MovementState = EMovementState::EMS_Idle;
	EActionState ActionState = EActionState::EAS_Idle;
	EArmedState ArmedState = EArmedState::EAS_Unarmed;

	class APlayerBase* PlayerBaseRef;

};
