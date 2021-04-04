#include "AutoSiegePlayerController.h"

#include "Components/TextBlock.h"

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

void AAutoSiegePlayerController::SelectHero(APortrait* hero)
{
	for (int i = 0; i < HeroSelectPortraits.Num(); i++)
	{
		if (HeroSelectPortraits[i] == hero)
		{
			HeroPortrait = hero;
			continue;
		}

		GetWorld()->DestroyActor(HeroSelectPortraits[i]);
	}

	HeroSelectPortraits.Reset();

	Server_PlayerReady(hero->Name);
}

void AAutoSiegePlayerController::Server_PlayerReady_Implementation(FName HeroName)
{
	if (IsPlayerReady)
		return;

	IsPlayerReady = true;

	GameState_Ref->NumberOfReadyPlayers++;
	GameState_Ref->Heroes[PlayerState_Ref->PlayerIndex] = HeroName;

	GameMode_Ref->CheckAllPlayersReady();
}

void AAutoSiegePlayerController::Server_RefreshShop_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

void AAutoSiegePlayerController::Server_UpgradeShop_Implementation()
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
		}

		return;
	}

	// TODO: Error message "Cannot afford to upgrade shop!"
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Cannot afford to upgrade shop!");
}

void AAutoSiegePlayerController::Server_FreezeShop_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}


void AAutoSiegePlayerController::Server_BuyCard_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}


void AAutoSiegePlayerController::Server_SellCard_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

void AAutoSiegePlayerController::Server_PlayCard_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

void AAutoSiegePlayerController::Server_ReorderCards_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

void AAutoSiegePlayerController::Server_CastHeroAbility_Implementation()
{
	if (!HasAuthority())
		return;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server: Cast Hero!");
	// Do something
	Client_DoSomething(5);
}

void AAutoSiegePlayerController::Client_DoSomething_Implementation(int32 i)
{
	if (HasAuthority())
		return;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Client: Do Something!");
	
	AAutoSiegeHUD* hud = Cast<AAutoSiegeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	UAutoSiegeUserWidget* uw = (UAutoSiegeUserWidget*)hud->CurrentWidget;
	uw->UpdateShopUpgradeCost(i);
}

void AAutoSiegePlayerController::Client_PresentHeroes_Implementation(const TArray<FName>& Heroes)
{
	if (HasAuthority())
		return;
	
	PresentHeroes(Heroes);
}
