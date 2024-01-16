#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PF_REFACTORING_API UHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		void HPChanged(float InMaxHP, float InHP);

private:
	UPROPERTY()
		class UHealthBarWidget* HealthBarWidget;
};
