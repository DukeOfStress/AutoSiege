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

void AAutoSiegePlayerController::Server_SelectHero_Implementation(FName HeroName)
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

void AAutoSiegePlayerController::Client_HeroApproved_Implementation(FName HeroName)
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

void AAutoSiegePlayerController::Client_BeginShop_Implementation(const TArray<int32>& Cards)
{
	if (HasAuthority())
		return;

	BP_BeginShop(Cards);
}