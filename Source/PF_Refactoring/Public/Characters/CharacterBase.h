#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHitInterface.h"
#include "CharacterBase.generated.h"

class UAnimMontage;
class UMontageComponent;
class UAttributeComponent;

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

protected:
	// MontageComponent, Must CreateDefaultSubobject in Constructor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		UMontageComponent* MontageComponent;

	// AttributeComponent, Must CreateDefaultSubobject in Constructor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorComponents", meta = (AllowPrivateAccess = "true"))
		UAttributeComponent* AttributeComponent;


public:
	// IHitInterface implemantation
	virtual void GetHit_Implementation(const FVector& ImpactPoint, float Strength, AActor* HitActor) override;

	/** Hit React */
	virtual void HitReact(const FVector& ImpactPoint, float Strength);

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE UMontageComponent* GetMontageComponent() { return MontageComponent; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UAttributeComponent* GetAttributeComponent() { return AttributeComponent; }

	UFUNCTION(BlueprintCallable)
		virtual void ReceiveDamage(float InDamage);

};
