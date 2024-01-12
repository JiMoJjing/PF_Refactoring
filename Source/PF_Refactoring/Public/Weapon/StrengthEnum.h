#pragma once

UENUM(BlueprintType)
enum class EStrengthType : uint8
{
	EST_None UMETA(DisplayName = "None"),
	EST_Normal UMETA(DisplayName = "Normal"),
	EST_Middle UMETA(DisplayName = "Middle"),
	EST_Heavy UMETA(DisplayName = "Heavy"),
};