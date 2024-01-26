// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "WeaponSword.generated.h"

/**
 * 
 */
UCLASS()
class PF_REFACTORING_API AWeaponSword : public AWeaponBase
{
	GENERATED_BODY()

protected:

	AWeaponSword();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/*For overlap enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxComponents")
		class UBoxComponent* BoxCollision;

	/*For Trace Start, End / For set boxcollision extend and relative location*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponents")
		class USceneComponent* Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponents")
		class USceneComponent* End;

	/*For divide enemy hitted reaction*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strength")
		float NormalStrength = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strength")
		float NowStrength;

	TArray<AActor*> IgnoreActors;

public:
	/* Attach Start, End scene component to skeletalmesh's socket(Start, End) */
	UFUNCTION(BlueprintCallable)
		void InitSceneComponents();

	/* Calculate and set box collision size, relative location */
	UFUNCTION(BlueprintCallable)
		void InitBoxCollision();

	virtual void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName) override;

	/*Query Only <-> No Collision , Called from AnimNotifyState_WeaponCollision*/
	UFUNCTION(BlueprintCallable)
		void SetBoxCollisionEnabled(ECollisionEnabled::Type InType);

	/*if enemy OnBoxBeginOverlap, Trace Start*/
	UFUNCTION(BlueprintCallable)
		void BoxTrace(FHitResult& BoxHit);

	/*Set Strength, Called from AnimNotify_SetStrength*/
	UFUNCTION(BlueprintCallable)
		void SetStrengthNormal() { NowStrength = NormalStrength; }

	UFUNCTION(BlueprintCallable)
		void SetStrengthMiddle() { NowStrength = NormalStrength * 2.f; }

	UFUNCTION(BlueprintCallable)
		void SetStrengthHeavy() { NowStrength = NormalStrength * 3.f; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetStrength() { return NowStrength; }

	virtual void AttackFinished() override;

	UFUNCTION(BlueprintCallable)
		void EmptyIgnoreActors();

protected:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
