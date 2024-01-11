#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IHitInterface.h"
#include "CharacterBase.generated.h"

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


	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* HitActor) override;

};
