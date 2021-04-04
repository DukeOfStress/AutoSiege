#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "AutoSiegeGameStateBase.h"
#include "AutoSiegePlayerState.h"
#include "AutoSiegeHUD.h"
#include "AutoSiegeUserWidget.h"
#include "Portrait.h"

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
	AAutoSiegeGameModeBase* GameMode_Ref;
	AAutoSiegeGameStateBase* GameState_Ref;
	AAutoSiegePlayerState* PlayerState_Ref;

	TArray<APortrait*> HeroSelectPortraits;
	APortrait* HeroPortrait;

	bool IsPlayerReady = false;

	UFUNCTION(BlueprintCallable)
	void SelectHero(APortrait* hero);
	
	UFUNCTION(Server, Reliable)
	void Server_PlayerReady(FName HeroName);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_UpgradeShop();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_RefreshShop();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_FreezeShop();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_BuyCard();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SellCard();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_PlayCard();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ReorderCards();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_CastHeroAbility();








	UFUNCTION(Client, Reliable)
	void Client_DoSomething(int32 i);

	UFUNCTION(Client, Reliable)
	void Client_PresentHeroes(const TArray<FName>& Heroes);

	UFUNCTION(BlueprintImplementableEvent)
	void PresentHeroes(const TArray<FName>& Heroes);












};


/*

 Player Data:
  - Cards in lineup
  - Cards in hand
  - Shop tier level
  - Shop offering
  - Shop is frozen
  - Current and total gold

*/