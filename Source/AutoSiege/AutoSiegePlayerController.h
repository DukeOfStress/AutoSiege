#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AutoSiegeGameStateBase.h"
#include "AutoSiegePlayerState.h"
#include "AutoSiegeUserWidget.h"
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

	
	UFUNCTION(Client, Reliable)
	void Client_PresentHeroes(const TArray<FName>& Heroes);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_PresentHeroes(const TArray<FName>& Heroes);


	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SelectHero(const FName HeroName);

	UFUNCTION(Client, Reliable)
	void Client_HeroApproved(const FName HeroName);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HeroApproved(const FName HeroName);


	UFUNCTION(Client, Reliable)
	void Client_AllPlayersReady(const TArray<FName>& Heroes);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_AllPlayersReady(const TArray<FName>& Heroes);

	
	UFUNCTION(Client, Reliable)
	void Client_BeginShop(const int32 Gold, const TArray<int32>& Cards);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_BeginShop(const int32 Gold, const TArray<int32>& Cards);


	UFUNCTION(Server, Reliable)
	void Server_UpgradeShopTier();

	UFUNCTION(Client, Reliable)
	void Client_UpgradeShopTier(const int32 NewShopTier);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpgradeShopTier(const int32 NewShopTier);


	UFUNCTION(Server, Reliable)
	void Server_ToggleFreezeShop();

	UFUNCTION(Client, Reliable)
	void Client_ToggleFreezeShop(const bool IsShopFrozen);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ToggleFreezeShop(const bool IsShopFrozen);
};

/*

 Player Data:
  - Cards in lineup
  - Cards in hand

*/