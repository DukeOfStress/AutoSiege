#include "AutoSiegePlayerController.h"
#include "AutoSiegeGameModeBase.h"
#include "ISourceControlProvider.h"
#include "Portrait.h"

AAutoSiegePlayerController::AAutoSiegePlayerController()
{
	bAutoManageActiveCameraTarget = false;
	bEnableClickEvents = true;
	bShowMouseCursor = true;
}

void AAutoSiegePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode_Ref = GetWorld()->GetAuthGameMode<AAutoSiegeGameModeBase>();
	GameState_Ref = GetWorld()->GetGameState<AAutoSiegeGameStateBase>();
	PlayerState_Ref = GetPlayerState<AAutoSiegePlayerState>();
}

TArray<FPlayerCard> AAutoSiegePlayerController::RefreshShopCards()
{
	int32 MaximumAllowedCards;
	switch (PlayerState_Ref->ShopTier)
	{
	    case 2:
	    case 3:
    		MaximumAllowedCards = 4;
    		break;
	    case 4:
	    case 5:
    		MaximumAllowedCards = 5;
    		break;
	    case 6:
    		MaximumAllowedCards = 6;
    		break;
	    case 1:
	    default:
    		MaximumAllowedCards = 3;
    		break;
	}

	if (!PlayerState_Ref->ShopFrozen)
	{
		GameMode_Ref->ReturnCardsToPool(PlayerState_Ref->ShopCards);
		PlayerState_Ref->ShopCards.Empty();
	}

	PlayerState_Ref->ShopFrozen = false;

	if (PlayerState_Ref->ShopCards.Num() < MaximumAllowedCards)
	{
	    const int32 CardsToDraw = MaximumAllowedCards - PlayerState_Ref->ShopCards.Num();
	    const TArray<FPlayerCard> NewPlayerCards = GameMode_Ref->GetCardsFromPool(PlayerState_Ref->ShopTier, CardsToDraw);

	    PlayerState_Ref->ShopCards.Append(NewPlayerCards);
	}

	return PlayerState_Ref->ShopCards;
}


void AAutoSiegePlayerController::Server_SelectHero_Implementation(const FName HeroName)
{
	if (!GameMode_Ref->AllowPlayerReady)
		return;

	if (IsPlayerReady)
		return;

	IsPlayerReady = true;

	PlayerState_Ref->Hero = HeroName;
	GameState_Ref->Heroes[PlayerState_Ref->PlayerIndex] = HeroName;

	Client_HeroApproved(HeroName);

	GameMode_Ref->CheckAllPlayersReady();
}

void AAutoSiegePlayerController::Client_PresentHeroes_Implementation(const TArray<FName>& Heroes)
{
	if (HasAuthority())
		return;
	
	BP_PresentHeroes(Heroes);
}

void AAutoSiegePlayerController::Client_HeroApproved_Implementation(const FName HeroName)
{
	if (HasAuthority())
		return;

	BP_HeroApproved(HeroName);
}

void AAutoSiegePlayerController::Client_AllPlayersReady_Implementation(const TArray<FName>& Heroes)
{
	if (HasAuthority())
		return;

	BP_AllPlayersReady(Heroes);
}

void AAutoSiegePlayerController::Client_BeginShop_Implementation(const int32 Gold, const TArray<FPlayerCard>& PlayerCards)
{
	if (HasAuthority())
		return;

	BP_BeginShop(Gold, PlayerCards);
}

void AAutoSiegePlayerController::Server_UpgradeShopTier_Implementation()
{
	if (!HasAuthority())
		return;

	bool Succeeded = false;
	if (PlayerState_Ref->Gold >= PlayerState_Ref->ShopUpgradePrice)
	{
		Succeeded = true;
		PlayerState_Ref->Gold -= PlayerState_Ref->ShopUpgradePrice;
		PlayerState_Ref->ShopTier++;

		switch (PlayerState_Ref->ShopTier)
		{
		case 2:
			PlayerState_Ref->ShopUpgradePrice = 7;
			break;
		case 3:
			PlayerState_Ref->ShopUpgradePrice = 8;
			break;
		case 4:
			PlayerState_Ref->ShopUpgradePrice = 9;
			break;
		case 5:
			PlayerState_Ref->ShopUpgradePrice = 10;
			break;
		case 6:
		default:
			PlayerState_Ref->ShopUpgradePrice = 9999;
			break;
		}
	}

	Client_UpgradeShopTier(Succeeded, PlayerState_Ref->ShopTier, PlayerState_Ref->ShopUpgradePrice, PlayerState_Ref->Gold);
}

void AAutoSiegePlayerController::Client_UpgradeShopTier_Implementation(const bool Succeeded, const int32 NewShopTier, const int32 NewShopUpgradePrice, const int32 NewGold)
{
	if (HasAuthority())
		return;

	BP_UpgradeShopTier(Succeeded, NewShopTier, NewShopUpgradePrice, NewGold);
}

void AAutoSiegePlayerController::Server_ToggleFreezeShop_Implementation()
{
	if (!HasAuthority())
		return;

	PlayerState_Ref->ShopFrozen = !PlayerState_Ref->ShopFrozen;
	Client_ToggleFreezeShop(PlayerState_Ref->ShopFrozen);
}

void AAutoSiegePlayerController::Client_ToggleFreezeShop_Implementation(const bool IsShopFrozen)
{
	if (HasAuthority())
		return;

	BP_ToggleFreezeShop(IsShopFrozen);
}

void AAutoSiegePlayerController::Server_RefreshShop_Implementation()
{
	if (!HasAuthority())
		return;

	bool Succeeded = false;
	if (PlayerState_Ref->Gold >= 1)
	{
		Succeeded = true;
		PlayerState_Ref->Gold -= 1;
		RefreshShopCards();
	}

	Client_RefreshShop(Succeeded, PlayerState_Ref->ShopCards, PlayerState_Ref->ShopFrozen, PlayerState_Ref->Gold);
}

void AAutoSiegePlayerController::Client_RefreshShop_Implementation(const bool Succeeded, const TArray<FPlayerCard>& NewCards, const bool IsShopFrozen, const int32 NewGold)
{
	if (HasAuthority())
		return;

	BP_RefreshShop(Succeeded, NewCards, IsShopFrozen, NewGold);
}
