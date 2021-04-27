#include "AutoSiegePlayerState.h"

#include "AutoSiegeHUD.h"
#include "AutoSiegeUserWidget.h"
#include "AutoSiegePlayerController.h"
#include "Portrait.h"

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
}

//void AAutoSiegePlayerState::OnRep_ChosenHero()
//{
//
//}
//
//void AAutoSiegePlayerState::OnRep_Gold()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "OnRep_Gold");
//}
//
//void AAutoSiegePlayerState::OnRep_ShopCards()
//{
//	AAutoSiegePlayerController* PlayerController = GetWorld()->GetFirstPlayerController<AAutoSiegePlayerController>();
//
//	if (GetOwner() != PlayerController)
//		return;
//
//
//}
//
//void AAutoSiegePlayerState::OnRep_ShopTier()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "OnRep_ShopTier");
//}
//
//
//void AAutoSiegePlayerState::OnRep_ShopUpgradePrice()
//{
//	AAutoSiegePlayerController* PlayerController = GetWorld()->GetFirstPlayerController<AAutoSiegePlayerController>();
//
//	if (GetOwner() != PlayerController)
//		return;
//
//	AAutoSiegeHUD* hud = Cast<AAutoSiegeHUD>(PlayerController->GetHUD());
//
//	UAutoSiegeUserWidget* uw = (UAutoSiegeUserWidget*)hud->CurrentWidget;
//	//uw->UpdateShopUpgradeCost(ShopUpgradePrice);
//}
