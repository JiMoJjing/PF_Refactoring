#include "Enemy/EnemyBase.h"

#include "ActorComponents/SwordMontageComponent.h"

AEnemyBase::AEnemyBase()
{
	MontageComponent = CreateDefaultSubobject<USwordMontageComponent>(TEXT("SwordMontageComponent"));
}
