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

	UFUNCTION(Server, unreliable, WithValidation)
	void Server_PlayerReady(FName HeroName);

private:
	ABoard* PlayerBoard;

};


/*

Player Actions:
 - Freeze shop
 - Upgrade shop
 - Re-roll shop
 - Buy card
 - Sell card
 - Play card
 - reorder they lineup
 - case their hero ability

 Player Data:
  - Cards in lineup
  - Cards in hand
  - Shop tier level
  - Shop offering
  - Shop is frozen
  - Current and total gold

*/