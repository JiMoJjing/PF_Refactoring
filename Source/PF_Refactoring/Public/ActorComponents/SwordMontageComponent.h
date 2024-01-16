#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/MontageComponent.h"
#include "SwordMontageComponent.generated.h"

class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_REFACTORING_API USwordMontageComponent : public UMontageComponent
{
	GENERATED_BODY()

public:	
	USwordMontageComponent();

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
		class UAttributeComponent* AttributeComponentRef;

private:
	UPROPERTY(EditAnywhere, Category = "Montages | Equip", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Attack", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* IdleWalkAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Attack", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* RunningAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Attack", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* JumpAttackMontage;

public:
	// Check Ref, false is nullptr
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE bool CheckRef() const;

	// Unarmed <-> Armed, Called from AnimNotify_Drawning, AnimNotify_Sheathing
	UFUNCTION(BlueprintCallable)
		void PlayEquipMontage();

	// Attack, Called from APlayerBase::LeftMouseButtonPressed
	UFUNCTION(BlueprintCallable)
		void PlayAttackMontage();

	// JumpToSection, Called from AnimNotify_JumpToSection
	UFUNCTION(BlueprintCallable)
		void PlayNextSection(const FName& InSectionName);
	
	// Called from AnimNotifyState_EanbleCombo
	UFUNCTION(BlueprintCallable)
		void SetEnableCombo(bool InEnableCombo) { bEnableCombo = InEnableCombo; }

	// Called from APlayerBase::AttackFinished
	UFUNCTION(BlueprintCallable)
		void AttackMontageFinished();

private:
	bool bEnableCombo = false;
	bool bNextCombo = false;
};
