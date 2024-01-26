#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_REFACTORING_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
protected:
	UPROPERTY()
		class APlayerBase* PlayerBaseRef;

	UPROPERTY()
		class AActor* TargetActor;

public:
	UFUNCTION()
		void SearchTarget();

	UFUNCTION()
		void EndTargeting();

	void SphereTrace(TArray<FHitResult>& InHitresults);

	void SetTarget(TArray<AActor*, FDefaultAllocator>& InActors);

	float GetTheta(const FVector& InPlayerLocation, const FVector& InPlayerForwardVector, const FVector& InTargetLocation);

private:
	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceRadius = 1000.f;

	UPROPERTY(EditAnywhere, Category = "FOV")
		float InScreenRange = 45.f;

};
