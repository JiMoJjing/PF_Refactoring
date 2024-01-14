#include "Weapon/WeaponBase.h"
#include "Engine/SkeletalMesh.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"

#include "Interfaces/IHitInterface.h"

#include "Utilities.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(GetRootComponent());

	BoxCollision->SetCollisionProfileName(TEXT("Custom"));
	BoxCollision->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);


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

	NowStrength = NowStrength;
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
	float distanceStartRoot = FVector::Dist(Mesh->GetSocketLocation(TEXT("Start")), Mesh->GetBoneLocation("Root"));

	BoxCollision->SetRelativeLocation(FVector(0.f,0.f, distanceStartRoot + (distanceStartEnd / 2)));
	BoxCollision->SetBoxExtent(FVector(10.f, 10.f, distanceStartEnd / 2));
}

void AWeaponBase::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules transformRules(EAttachmentRule::KeepRelative, true);
	Mesh->AttachToComponent(InParent, transformRules, InSocketName);
}

void AWeaponBase::SetBoxCollisionEnabled(ECollisionEnabled::Type InType)
{
	BoxCollision->SetCollisionEnabled(InType);
}

void AWeaponBase::BoxTrace(FHitResult& BoxHit)
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.AddUnique(GetOwner());

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start->GetComponentLocation(),
		End->GetComponentLocation(),
		FVector(10.f),
		Start->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		IgnoreActors,
		EDrawDebugTrace::ForDuration,
		BoxHit,
		true,
		FLinearColor::Green,
		FLinearColor::Red,
		2.f
	);
}

void AWeaponBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult hitResult;

	BoxTrace(hitResult);

	if (hitResult.GetActor())
	{
		IIHitInterface* hitInterface = Cast<IIHitInterface>(hitResult.GetActor());
		if (hitInterface)
		{
			hitInterface->Execute_GetHit(hitResult.GetActor(), hitResult.ImpactPoint, NowStrength, GetOwner());
		}
	}
}

void AWeaponBase::AttackFinished()
{
	SetStrengthNormal();
}