#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

#include "AutoSiegePlayerState.generated.h"

UCLASS()
class AUTOSIEGE_API AAutoSiegePlayerState : public APlayerState
{

	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	int PlayerIndex;

	UPROPERTY(Replicated)
	uint32 Gold;

	UPROPERTY(Replicated)
	uint32 ShopTier;

	UPROPERTY(Replicated)
	uint32 ShopUpgradePrice;

	UPROPERTY(Replicated)
	TArray<uint32> ShopCards;

};
