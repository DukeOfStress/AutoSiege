#pragma once
#include "FPlayerCard.h"
#include "FBattle.generated.h"

UENUM()
enum EBattleActionType
{
	CardAttacks
};

USTRUCT(BlueprintType)
struct FBattleAction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentPlayer;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBattleActionType> Type;

	UPROPERTY(BlueprintReadOnly)
	int32 AttackerUID;

	UPROPERTY(BlueprintReadOnly)
	int32 DefenderUID;

	UPROPERTY(BlueprintReadOnly)
	int32 NewAttackerHealth;

	UPROPERTY(BlueprintReadOnly)
	int32 NewDefenderHealth;
};

USTRUCT(BlueprintType)
struct FBattle
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FBattleAction> Actions;

	UPROPERTY(BlueprintReadOnly)
	bool IsDraw;
	
	UPROPERTY(BlueprintReadOnly)
	int32 LosingPlayer;

	UPROPERTY(BlueprintReadOnly)
	int32 NewLosingPlayerHealth;
};

USTRUCT(BlueprintType)
struct FBattleOpponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 ID;

	UPROPERTY(BlueprintReadOnly)
	FName Hero;

	UPROPERTY(BlueprintReadOnly)
	int32 StartingHealth;

	UPROPERTY(BlueprintReadOnly)
	TArray<FPlayerCard> Cards;
};
