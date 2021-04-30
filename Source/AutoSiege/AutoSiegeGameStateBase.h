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
	int32 RoundNumber = 1;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RoundTimer)
	float RoundTimer = 15.f;

	UPROPERTY(BlueprintReadOnly)
	int32 TotalNumberOfPlayers = 3;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Heroes)
	TArray<FName> Heroes;

	TEnumAsByte<GameStage> CurrentStage;

	
	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_RoundTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_Heroes();

};
