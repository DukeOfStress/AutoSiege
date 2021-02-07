#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AutoSiegeGameStateBase.generated.h"

UENUM()
enum GameStage
{
	PlayerJoin,
	HeroSelect
};

UCLASS()
class AUTOSIEGE_API AAutoSiegeGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
	float RoundTimer;

	UPROPERTY(Replicated)
	int PlayerHealth [8];

	UPROPERTY(Replicated)
	int NumberOfConnectedPlayers;

	const int TotalNumberOfPlayers = 3;

	GameStage CurrentStage;

	// Current matchups
};
