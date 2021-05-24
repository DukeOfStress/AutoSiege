#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "AutoSiegeGameStateBase.h"
#include "AutoSiegePlayerState.h"
#include "AutoSiegeUserWidget.h"
#include "FBattle.h"
#include "FPlayerCard.h"
#include "AutoSiegePlayerController.generated.h"

// Forward declaration to enable circular reference
class AAutoSiegeGameModeBase;

UCLASS(Blueprintable, BlueprintType)
class AUTOSIEGE_API AAutoSiegePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAutoSiegePlayerController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	AAutoSiegeGameModeBase* GameMode_Ref;

	UPROPERTY()
	AAutoSiegeGameStateBase* GameState_Ref;

	UPROPERTY()
	AAutoSiegePlayerState* PlayerState_Ref;

	bool IsPlayerReady = false;
	
	TArray<FPlayerCard> RefreshShopCards();

	
	UFUNCTION(Client, Reliable)
	void Client_PresentHeroes(const TArray<FName>& Heroes);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_PresentHeroes(const TArray<FName>& Heroes);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SelectHero(const FName HeroName);

	UFUNCTION(Client, Reliable)
	void Client_HeroApproved(const FName HeroName, const int32 Health);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HeroApproved(const FName HeroName, const int32 Health);


	UFUNCTION(Client, Reliable)
	void Client_AllPlayersReady(const TArray<FName>& Heroes);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_AllPlayersReady(const TArray<FName>& Heroes);

	
	UFUNCTION(Client, Reliable)
	void Client_BeginShop(const int32 Gold, const TArray<FPlayerCard>& PlayerCards, const int32 NextOpponent);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_BeginShop(const int32 Gold, const TArray<FPlayerCard>& PlayerCards, const int32 NextOpponent);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_UpgradeShopTier();

	UFUNCTION(Client, Reliable)
	void Client_UpgradeShopTier(const bool Succeeded, const int32 NewShopTier, const int32 NewShopUpgradePrice, const int32 NewGold);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpgradeShopTier(const bool Succeeded, const int32 NewShopTier, const int32 NewShopUpgradePrice, const int32 NewGold);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ToggleFreezeShop();

	UFUNCTION(Client, Reliable)
	void Client_ToggleFreezeShop(const bool IsShopFrozen);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ToggleFreezeShop(const bool IsShopFrozen);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_RefreshShop();

	UFUNCTION(Client, Reliable)
	void Client_RefreshShop(const bool Succeeded, const TArray<FPlayerCard>& NewCards, const int32 NewGold);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_RefreshShop(const bool Succeeded, const TArray<FPlayerCard>& NewCards, const int32 NewGold);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_BuyCard(const FPlayerCard CardToBuy);

	UFUNCTION(Client, Reliable)
	void Client_BuyCard(const bool Succeeded, const FPlayerCard BoughtCard, const int32 NewGold);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_BuyCard(const bool Succeeded, const FPlayerCard BoughtCard, const int32 NewGold);

	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_PlayCard(const FPlayerCard CardToPlay);

	UFUNCTION(Client, Reliable)
	void Client_PlayCard(const bool Succeeded, const FPlayerCard CardPlayed);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_PlayCard(const bool Succeeded, const FPlayerCard CardPlayed);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SellCard(const FPlayerCard CardToSell);

	UFUNCTION(Client, Reliable)
	void Client_SellCard(const bool Succeeded, const FPlayerCard CardSold, const int32 NewGold);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SellCard(const bool Succeeded, const FPlayerCard CardSold, const int32 NewGold);


	UFUNCTION(Client, Reliable)
	void Client_ShowBattle(const FBattleOpponent Opponent, const FBattle Battle);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ShowBattle(const FBattleOpponent Opponent, const FBattle Battle);


	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_BattleFinished();
};
