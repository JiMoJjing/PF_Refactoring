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

protected:
	// Reference
	UPROPERTY()
		class ACharacterBase* CharacterBaseRef;

	UPROPERTY()
		class UAnimInstance* AnimInstanceRef;

protected:
	// Hit React Montages
	UPROPERTY(EditAnywhere, Category = "Montages | Hit", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* HitNormalMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Hit", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* HitMiddleMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Hit", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* HitHeavyMontage;

	// WakeUp Montage
	UPROPERTY(EditAnywhere, Category = "Montages | Hit", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* WakeUpMontage;

public:
	UFUNCTION(BlueprintCallable)
		void PlayMontageSection(UAnimMontage* InAnimMontage, const FName& SectionName);

	UFUNCTION(BlueprintCallable)
		void PlayMontage(UAnimMontage* InAnimMontage);

	UFUNCTION(BlueprintCallable)
		void PlayHitNormalMontage(const FName& SectionName);

	UFUNCTION(BlueprintCallable)
		void PlayHitMiddleMontage(const FName& SectionName);

	UFUNCTION(BlueprintCallable)
		void PlayHitHeavyMontage();

	UFUNCTION(BlueprintCallable)
		void PlayWakeUpMontage();
};
