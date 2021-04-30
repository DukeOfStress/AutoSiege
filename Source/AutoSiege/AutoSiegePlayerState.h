#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AutoSiegePlayerState.generated.h"

UCLASS()
class AUTOSIEGE_API AAutoSiegePlayerState : public APlayerState
{

	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	int PlayerIndex;

	UPROPERTY(Replicated)
	FName Hero;

	UPROPERTY(Replicated)
	uint32 Gold;

	uint32 ShopTier;

	UPROPERTY(Replicated)
	uint32 ShopUpgradePrice;

	TArray<int32> ShopCards;

	bool ShopFrozen = false;

};
