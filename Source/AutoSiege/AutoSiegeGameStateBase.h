#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AutoSiegeGameStateBase.generated.h"

UENUM(BlueprintType)
enum GameStage
{
	HeroSelect,
	Shop,
	Battle
};

struct FMatchUp
{
	int32 Player1;
	int32 Player2;
};

UCLASS()
class AUTOSIEGE_API AAutoSiegeGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	int32 RoundNumber = 1;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RoundTimer)
	float RoundTimer = 15.f;

	UPROPERTY(BlueprintReadOnly)
	int32 TotalNumberOfPlayers = 4;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Heroes)
	TArray<FName> Heroes;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TEnumAsByte<GameStage> CurrentStage;

	TArray<FMatchUp> MatchUps;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_RoundTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_Heroes();

};
