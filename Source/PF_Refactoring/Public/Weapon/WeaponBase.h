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
	// For overlap enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxComponents")
		class UBoxComponent* BoxCollision;
	// Weapon Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMeshComponents")
		class USkeletalMeshComponent* Mesh;
	// For Trace Start, End / For set boxcollision extend and relative location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponents")
		class USceneComponent* Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponents")
		class USceneComponent* End;
	// Now skeletal mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMeshComponents")
		class USkeletalMesh* SkeletalMesh;
	// For divide enemy's hitted reaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strength")
		float NormalStrength = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strength")
		float NowStrength;

public:
	// Attach Start, End scene component to skeletalmesh's socket(Start, End)
	UFUNCTION(BlueprintCallable)
		void InitSceneComponents();
	// Calculate and set box collision size, relative location
	UFUNCTION(BlueprintCallable)
		void InitBoxCollision();
	// For Equip, Unequip. Called from AnimNotify_Drawing, Sheathing
	UFUNCTION(BlueprintCallable)
		void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	// Query Only <-> No Collision , Called from AnimNotifyState_WeaponCollision
	UFUNCTION(BlueprintCallable)
		void SetBoxCollisionEnabled(ECollisionEnabled::Type InType);
	// if enemy OnBoxBeginOverlap, Trace Start
	UFUNCTION(BlueprintCallable)
		void BoxTrace(FHitResult& BoxHit);
	// Set Strength, Called from AnimNotify_SetStrength
	UFUNCTION(BlueprintCallable)
		void SetStrengthNormal() { NowStrength = NormalStrength; }

	UFUNCTION(BlueprintCallable)
		void SetStrengthMiddle() { NowStrength = NormalStrength * 2.f; }

	UFUNCTION(BlueprintCallable)
		void SetStrengthHeavy() { NowStrength = NormalStrength * 3.f; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetStrength() { return NowStrength; }
	// Called from APlayerBase::AttackFinished
	UFUNCTION(BlueprintCallable)
		void AttackFinished();
protected:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
