#pragma once

#include "FPlayerCard.generated.h"

USTRUCT(BlueprintType)
struct FPlayerCard
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 UID;

	UPROPERTY(BlueprintReadOnly)
	int32 BaseCardID;

	UPROPERTY(BlueprintReadOnly)
	FName BaseCardName;

	UPROPERTY(BlueprintReadOnly)
	int32 Power;

	UPROPERTY(BlueprintReadOnly)
	int32 Health;
};
