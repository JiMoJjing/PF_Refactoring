#include "Weapon/WeaponBase.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"

#include "Engine/SkeletalMesh.h"

#include "Utilities.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(GetRootComponent());

	//BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Start = CreateDefaultSubobject<USceneComponent>(TEXT("Start"));
	End = CreateDefaultSubobject<USceneComponent>(TEXT("End"));

}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBoxBeginOverlap);
	if (SkeletalMesh)
	{
		Mesh->SetSkeletalMesh(SkeletalMesh, false);
		InitSceneComponents();
		InitBoxCollision();
	}
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::InitSceneComponents()
{
	FAttachmentTransformRules transformRules(EAttachmentRule::KeepRelative, true);
	Start->AttachToComponent(Mesh, transformRules, TEXT("Start"));
	End->AttachToComponent(Mesh, transformRules, TEXT("End"));
}

void AWeaponBase::InitBoxCollision()
{
	float distanceStartEnd = FVector::Dist(Mesh->GetSocketLocation(TEXT("Start")), Mesh->GetSocketLocation(TEXT("End")));
	float distanceEndRoot = FVector::Dist(Mesh->GetSocketLocation(TEXT("End")), Mesh->GetBoneLocation("Root"));

	BoxCollision->SetRelativeLocation(FVector(0.f,0.f, distanceEndRoot + (distanceStartEnd / 2)));
	BoxCollision->SetBoxExtent(FVector(8.f, 8.f, distanceStartEnd / 2));
}

void AWeaponBase::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules transformRules(EAttachmentRule::KeepRelative, true);
	Mesh->AttachToComponent(InParent, transformRules, InSocketName);
}

void AWeaponBase::EnableCollision(ECollisionEnabled::Type InType)
{
	BoxCollision->SetCollisionEnabled(InType);
}

void AWeaponBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CLog::Print(OverlappedComponent->GetName());
}

