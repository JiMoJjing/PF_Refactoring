#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerBase.h"
#include "PlayerSword.generated.h"

class USwordMontageComponent;

UCLASS()
class PF_REFACTORING_API APlayerSword : public APlayerBase
{
	GENERATED_BODY()

public:
	APlayerSword();

protected:
	UPROPERTY()
		USwordMontageComponent* SwordMontageComponentRef;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void LeftMouseButtonStarted() override;

	virtual void TabStarted() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE USwordMontageComponent* GetSwordMontageComponent() { return SwordMontageComponentRef; }

	virtual void AttackFinished() override;

};
