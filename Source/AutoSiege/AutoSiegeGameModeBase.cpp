#include "AutoSiegeGameModeBase.h"
#include "AutoSiegeGameStateBase.h"

AAutoSiegeGameModeBase::AAutoSiegeGameModeBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	GameStateClass = AAutoSiegeGameStateBase::StaticClass();
	PlayerControllerClass = AAutoSiegePlayerController::StaticClass();
	PlayerStateClass = AAutoSiegePlayerState::StaticClass();
	
	//HeroList = 

	bPauseable = false;
}

void AAutoSiegeGameModeBase::BeginPlay()
{

	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameMode::BeginPlay"));

}

void AAutoSiegeGameModeBase::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);

	if( PlayerControllerArray.Num() <= MAX_NUM_PLAYERS ){
		PlayerControllerArray.AddUnique((AAutoSiegePlayerController*)NewPlayer);
		PlayerStateArray.AddUnique((AAutoSiegePlayerState*)(NewPlayer->PlayerState));

		auto ps = (AAutoSiegePlayerState*)(NewPlayer->PlayerState);
		ps->PlayerIndex = PlayerControllerArray.Num() - 1;
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GameMode::PostLogin - %d"), ps->PlayerIndex));


	}

}
