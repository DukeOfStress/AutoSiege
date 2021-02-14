#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "AutoSiegeGameStateBase.h"
#include "AutoSiegePlayerState.h"
#include "Board.h"
#include "Portrait.h"

#include "AutoSiegePlayerController.generated.h"

UCLASS()
class AUTOSIEGE_API AAutoSiegePlayerController : public APlayerController
{

	GENERATED_BODY()

public:
	AAutoSiegePlayerController();

protected:
	virtual void BeginPlay() override;

public:
	AAutoSiegeGameStateBase* GameState_Ref;
	AAutoSiegePlayerState* PlayerState_Ref;

	TArray<APortrait*> HeroSelectPortraits;
	APortrait* HeroPortrait;

	bool PlayerReadyCheck[8] = { false };

	UFUNCTION(BlueprintCallable)
	void SelectHero(APortrait* hero);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlayerReady(FName HeroName);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_UpgradeShop();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_RefreshShop();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_FreezeShop();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_BuyCard();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_SellCard();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_PlayCard();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_ReorderCards();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_CastHeroAbility();

	UPROPERTY(BlueprintReadOnly)
	ABoard* PlayerBoard;

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