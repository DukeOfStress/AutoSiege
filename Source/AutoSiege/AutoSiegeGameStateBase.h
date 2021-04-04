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
	FName Heroes[8];

	TEnumAsByte<GameStage> CurrentStage;

private:
	UFUNCTION()
	void OnRep_RoundTimer();

	UFUNCTION()
	void OnRep_NumberOfReadyPlayers();

};
