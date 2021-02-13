#include "Portrait.h"

APortrait::APortrait()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APortrait::OnUpdatePortrait(FName HeroName)
{
	Name = HeroName;
	ReceiveOnUpdatePortrait(HeroName);
}