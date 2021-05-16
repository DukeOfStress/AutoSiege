#pragma once
#include "FPlayerCard.h"
#include "FBattle.generated.h"

UENUM()
enum EBattleActionType
{
	CardAttacks,
	CardTakesDamage,
	CardTaunts,
	PlayerTakesDamage
};

USTRUCT(BlueprintType)
struct FBattleAction
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FPlayerCard Self;
	
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBattleActionType> Type;
	
	UPROPERTY(BlueprintReadOnly)
	int32 Damage;
	
	UPROPERTY(BlueprintReadOnly)
	FPlayerCard Target;
};

USTRUCT(BlueprintType)
struct FBattle
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	int32 Player1;

	UPROPERTY(BlueprintReadOnly)
	int32 Player2;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FBattleAction> Actions;
};
