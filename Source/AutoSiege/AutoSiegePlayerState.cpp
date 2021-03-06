#include "AutoSiegePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AutoSiegeUserWidget.h"

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
    DOREPLIFETIME(AAutoSiegePlayerState, ShopTier);
}
