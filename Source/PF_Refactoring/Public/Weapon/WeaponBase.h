#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class PF_REFACTORING_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	/*Weapon Mesh*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMeshComponents")
		class USkeletalMeshComponent* Mesh;

	/*Now skeletal mesh*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMeshComponents")
		class USkeletalMesh* SkeletalMesh;

public:
	/* For Equip, Unequip.Called from AnimNotify_Drawing, Sheathing */
	UFUNCTION(BlueprintCallable)
		virtual void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	/*Called from APlayerBase::AttackFinished*/
	UFUNCTION(BlueprintCallable)
		virtual void AttackFinished();
};
