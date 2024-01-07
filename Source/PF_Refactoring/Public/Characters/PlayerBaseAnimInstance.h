#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/StateEnums.h"

#include "PlayerBaseAnimInstance.generated.h"

UCLASS()
class PF_REFACTORING_API UPlayerBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
		void ArmedStateChanged(EArmedState InArmedState);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector Velocity;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Yaw;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MoveDirection;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bMoving;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsFalling;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float InterpSpeed = 5.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EArmedState ArmedState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class APlayerBase* PlayerBaseRef;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCharacterMovementComponent* MovementComponentRef;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UStateComponent* StateComponentRef;

};
