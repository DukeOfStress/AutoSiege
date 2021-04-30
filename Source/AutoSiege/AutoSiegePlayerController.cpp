#include "AutoSiegePlayerController.h"
#include "AutoSiegeGameModeBase.h"
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

void AAutoSiegePlayerController::Client_BeginShop_Implementation(const int32 Gold, const TArray<int32>& Cards)
{
	if (HasAuthority())
		return;

	BP_BeginShop(Gold, Cards);
}

void AAutoSiegePlayerController::Server_UpgradeShopTier_Implementation()
{
	if (!HasAuthority())
		return;

	if (PlayerState_Ref->Gold >= PlayerState_Ref->ShopUpgradePrice)
	{
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

	Client_UpgradeShopTier(PlayerState_Ref->ShopTier);
}

void AAutoSiegePlayerController::Client_UpgradeShopTier_Implementation(const int32 NewShopTier)
{
	if (HasAuthority())
		return;

	BP_UpgradeShopTier(NewShopTier);
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
