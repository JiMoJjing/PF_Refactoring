#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHitInterface.h"
#include "CharacterBase.generated.h"

class UAnimMontage;

UCLASS()
class PF_REFACTORING_API ACharacterBase : public ACharacter, public IIHitInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// Hit React Montages
	UPROPERTY(EditAnywhere, Category = "Montages | Hit", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* HitMiddleMontage;

	UPROPERTY(EditAnywhere, Category = "Montages | Hit", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* HitNormalMontage;

public:
	// IHitInterface implemantation
	virtual void GetHit_Implementation(const FVector& ImpactPoint, float Strength, AActor* HitActor) override;

	/** Hit React */
	void HitReact(const FVector& ImpactPoint, float Strength);

	UFUNCTION()
		void PlayMontageWithSection(UAnimMontage* InAnimMontage, const FName& SectionName);

};
