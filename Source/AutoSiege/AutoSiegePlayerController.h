#pragma once

#include "CoreMinimal.h"

#include "AutoSiegeGameStateBase.h"
#include "AutoSiegePlayerState.h"
#include "Board.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

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

	DECLARE_EVENT(AAutoSiegePlayerController, FClientPostLoginEvent)
	FClientPostLoginEvent& OnClientPostLoginEvent() { return ClientPostLoginEvent; };

	bool enableInHandMovementRotation;
	void SetCardLocation( /*3DCard*/ AActor card, FVector holdLocation, FRotator rotation);

	UFUNCTION(BlueprintCallable, Server, unreliable, WithValidation)
	void Server_PlayerReady();


private:
	FClientPostLoginEvent ClientPostLoginEvent;
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