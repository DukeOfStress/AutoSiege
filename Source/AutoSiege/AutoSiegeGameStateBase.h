#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "AutoSiegeGameStateBase.generated.h"

UENUM()
enum GameStage
{
	PlayerJoin,
	HeroSelect,
	Shop,
	Battle
};

UCLASS()
class AUTOSIEGE_API AAutoSiegeGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(ReplicatedUsing = OnRep_RoundTimer)
		float RoundTimer = 60.f;

	int NumberOfConnectedPlayers = 0;

	UPROPERTY(ReplicatedUsing = OnRep_NumberOfReadyPlayers)
	int NumberOfReadyPlayers = 0;

	const int TotalNumberOfPlayers = 3;

	UPROPERTY(Replicated)
	FName Heroes[3];  // TODO: Make sure this matches TotalNumberOfPlayers
					  // What happens when people don't connect to the game
					  // Arguably, a game with 2-8 players is valid? ...or do we cancel the game if not enough
					  // players are connected. Or do we let the AI take over??

	TEnumAsByte<GameStage> CurrentStage;

private:
	UFUNCTION()
	void OnRep_RoundTimer();

	UFUNCTION()
	void OnRep_NumberOfReadyPlayers();

};
