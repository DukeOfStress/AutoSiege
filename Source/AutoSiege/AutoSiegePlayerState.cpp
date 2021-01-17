#include "AutoSiegePlayerState.h"

AAutoSiegePlayerState::AAutoSiegePlayerState() 
{
    //bReplicates = true;
}

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
}