#include "AutoSiegePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AutoSiegeUserWidget.h"

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
    DOREPLIFETIME(AAutoSiegePlayerState, Hero);
    DOREPLIFETIME(AAutoSiegePlayerState, Gold);
    DOREPLIFETIME(AAutoSiegePlayerState, ShopCards);
    DOREPLIFETIME(AAutoSiegePlayerState, ShopTier);
    DOREPLIFETIME(AAutoSiegePlayerState, ShopUpgradePrice);
}
