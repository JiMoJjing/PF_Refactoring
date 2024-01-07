#pragma once

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	EMS_Idle UMETA(DisplayName = "Idle"),
	EMS_Walking UMETA(DisplayName = "Walking"),
	EMS_Running UMETA(DisplayName = "Running"),
	EMS_Jumping UMETA(DisplayName = "Jumping"),
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Idle UMETA(DisplayName = "Idle"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_Casting UMETA(DisplayName = "Casting"),
	EAS_Hitted UMETA(DisplayName = "Hitted"),
	EAS_KnockedDown UMETA(DisplayName = "KnockedDown"),
};

UENUM(BlueprintType)
enum class EArmedState : uint8
{
	EAS_Unarmed UMETA(DisplayName = "Unarmed"),
	EAS_Armed UMETA(DisplayName = "Armed"),
};
