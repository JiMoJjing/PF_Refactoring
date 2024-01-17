#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PF_REFACTORING_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float MaxHP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float HP;

public:
	UFUNCTION()
		void HPChanged(float InMaxHP, float InHP);
};
