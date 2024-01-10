#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MontageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_REFACTORING_API UMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMontageComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
		class APlayerBase* PlayerBaseRef;

	UPROPERTY()
		class UStateComponent* StateComponentRef;
	
	UPROPERTY()
		class UAnimInstance* AnimInstanceRef;

private:
	UPROPERTY(EditAnywhere, Category = "Montages | Equip", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Attack", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* IdleWalkComboMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Attack", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* RunningComboMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Attack", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* JumpComboMontage;

public:
	/** Check Ref, false is nullptr */
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE bool CheckRef() const;

	/** Unarmed <-> Armed */
	void PlayEquipMontage();

	/** Attack */
	UFUNCTION(BlueprintCallable)
		void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
		void PlayNextSection(const FName& InSectionName);

	UFUNCTION(BlueprintCallable)
		void SetEnableCombo(bool InEnableCombo) { bEnableCombo = InEnableCombo; }

	UFUNCTION(BlueprintCallable)
		void AttackMontageFinished();

private:
	bool bEnableCombo = false;
	bool bNextCombo = false;
};
