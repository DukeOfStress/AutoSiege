#include "AutoSiegePlayerState.h"

AAutoSiegePlayerState::AAutoSiegePlayerState() 
{
    AvailableHeroes = {};





    //bReplicates = true;
}

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
}