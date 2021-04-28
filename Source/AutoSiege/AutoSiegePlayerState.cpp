#include "AutoSiegePlayerState.h"

#include "AutoSiegeHUD.h"
#include "AutoSiegeUserWidget.h"
#include "AutoSiegePlayerController.h"
#include "Portrait.h"

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
    DOREPLIFETIME(AAutoSiegePlayerState, Gold);
    DOREPLIFETIME(AAutoSiegePlayerState, ShopCards);
    DOREPLIFETIME(AAutoSiegePlayerState, ShopTier);
    DOREPLIFETIME(AAutoSiegePlayerState, ShopUpgradePrice);
}
