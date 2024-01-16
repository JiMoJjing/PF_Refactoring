#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class PF_REFACTORING_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	AEnemyBase();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UHealthBarWidgetComponent* HealthBarWidgetComponent;

public:
	UFUNCTION(BlueprintCallable)
		void HPChanged(float InHPMax, float InHP);

	virtual void ReceiveDamage(float InDamage) override;
};
