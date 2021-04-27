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

void AAutoSiegePlayerController::Server_PlayerReady_Implementation(FName HeroName)
{

	if (IsPlayerReady)
		return;

	IsPlayerReady = true;

	GameState_Ref->NumberOfReadyPlayers++;
	GameState_Ref->Heroes[PlayerState_Ref->PlayerIndex] = HeroName;

	GameMode_Ref->CheckAllPlayersReady();

}

void AAutoSiegePlayerController::Client_PresentHeroes_Implementation(const TArray<FName>& Heroes)
{

	if (HasAuthority())
		return;
	
	BP_PresentHeroes(Heroes);

}
