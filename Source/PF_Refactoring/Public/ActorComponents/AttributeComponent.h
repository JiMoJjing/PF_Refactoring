#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHPChanged, float, MaxHP, float, HP);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_REFACTORING_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Speed
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float GetRunSpeed() const { return RunSpeed; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float GetWalkSpeed() const { return WalkSpeed; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float GetAttackSpeed() const { return AttackSpeed; }

	// Health
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float GetHP() const { return HP; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float GetMaxHP() const { return MaxHP; }



private:
	// Speed
	UPROPERTY(EditAnywhere, Category = "Attribute | Speed", meta = (AllowPrivateAccess = "true"))
		float RunSpeed = 600.f;
	
	UPROPERTY(EditAnywhere, Category = "Attribute | Speed", meta = (AllowPrivateAccess = "true"))
		float WalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, Category = "Attribute | AttackSpeed", meta = (AllowPrivateAccess = "true"))
		float AttackSpeed = 1.f;

	// HP
	UPROPERTY(EditAnywhere, Category = "Attribute | HP", meta = (AllowPrivateAccess = "true"))
		float HP;

	UPROPERTY(EditAnywhere, Category = "Attribute | HP", meta = (AllowPrivateAccess = "true"))
		float MaxHP;

public:
	/** HP DELEGATE
	* 
	*/
	UPROPERTY(BlueprintAssignable)
		FHPChanged OnHPChanged;
};
