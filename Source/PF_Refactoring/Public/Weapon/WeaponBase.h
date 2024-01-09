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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxComponents")
		class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMeshComponents")
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponents")
		class USceneComponent* Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneComponents")
		class USceneComponent* End;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMeshComponents")
		class USkeletalMesh* SkeletalMesh;

public:
	UFUNCTION(BlueprintCallable)
		void InitSceneComponents();

	UFUNCTION(BlueprintCallable)
		void InitBoxCollision();

	UFUNCTION(BlueprintCallable)
		void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	UFUNCTION(BlueprintCallable)
		void EnableCollision(ECollisionEnabled::Type InType);

protected:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
