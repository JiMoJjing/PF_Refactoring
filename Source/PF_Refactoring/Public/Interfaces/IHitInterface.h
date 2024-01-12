#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UIHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PF_REFACTORING_API IIHitInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
		void GetHit(const FVector& ImpactPoint, float Strength, AActor* HitActor);
};
