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

	bool IsPlayerReady = false;
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_PlayerReady(FName HeroName);

	UFUNCTION(Client, Reliable)
	void Client_PresentHeroes(const TArray<FName>& Heroes);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_PresentHeroes(const TArray<FName>& Heroes);

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