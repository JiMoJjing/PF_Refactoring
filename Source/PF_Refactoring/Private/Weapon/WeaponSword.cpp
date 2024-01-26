#include "Weapon/WeaponSword.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/SkeletalMesh.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"

#include "Characters/CharacterBase.h"
#include "Interfaces/IHitInterface.h"

#include "Utilities.h"

AWeaponSword::AWeaponSword()
{


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

void AWeaponSword::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponSword::OnBoxBeginOverlap);
	if (SkeletalMesh)
	{
		Mesh->SetSkeletalMesh(SkeletalMesh, false);
		InitSceneComponents();
		InitBoxCollision();
	}

	NowStrength = NowStrength;
}

void AWeaponSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponSword::InitSceneComponents()
{
	FAttachmentTransformRules transformRules(EAttachmentRule::KeepRelative, true);
	Start->AttachToComponent(Mesh, transformRules, TEXT("Start"));
	End->AttachToComponent(Mesh, transformRules, TEXT("End"));
}

void AWeaponSword::InitBoxCollision()
{
	float distanceStartEnd = FVector::Dist(Mesh->GetSocketLocation(TEXT("Start")), Mesh->GetSocketLocation(TEXT("End")));
	float distanceStartRoot = FVector::Dist(Mesh->GetSocketLocation(TEXT("Start")), Mesh->GetBoneLocation("Root"));

	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, distanceStartRoot + (distanceStartEnd / 2)));
	BoxCollision->SetBoxExtent(FVector(10.f, 10.f, distanceStartEnd / 2));
}

void AWeaponSword::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	Super::AttachMeshToSocket(InParent, InSocketName);
	CLog::Print(TEXT("WeaponSword"));
}

void AWeaponSword::SetBoxCollisionEnabled(ECollisionEnabled::Type InType)
{
	BoxCollision->SetCollisionEnabled(InType);
	EmptyIgnoreActors();
}

void AWeaponSword::BoxTrace(FHitResult& BoxHit)
{
	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start->GetComponentLocation(),
		End->GetComponentLocation(),
		FVector(10.f),
		Start->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		IgnoreActors,
		EDrawDebugTrace::ForDuration,
		BoxHit,
		true,
		FLinearColor::Green,
		FLinearColor::Red,
		2.f
	);
	if (BoxHit.GetActor())
	{
		IgnoreActors.AddUnique(BoxHit.GetActor());
	}
}

void AWeaponSword::AttackFinished()
{
	SetStrengthNormal();
	CLog::Print(TEXT("WeaponSword"));
}

void AWeaponSword::EmptyIgnoreActors()
{
	IgnoreActors.Empty();
}

void AWeaponSword::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult hitResult;

	BoxTrace(hitResult);

	if (hitResult.GetActor())
	{
		IIHitInterface* hitInterface = Cast<IIHitInterface>(hitResult.GetActor());
		if (hitInterface)
		{
			hitInterface->Execute_GetHit(hitResult.GetActor(), hitResult.ImpactPoint, NowStrength, GetOwner());
			UGameplayStatics::ApplyDamage(hitResult.GetActor(), 10.f, GetInstigator()->GetController(), this, UDamageType::StaticClass());
		}
	}
}
