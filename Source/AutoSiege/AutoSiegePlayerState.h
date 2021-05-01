#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AutoSiegePlayerState.generated.h"

UCLASS()
class AUTOSIEGE_API AAutoSiegePlayerState : public APlayerState
{

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Replicated)
	int PlayerIndex;

	FName Hero;

	int32 Gold;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ShopTier)
	int32 ShopTier;

	int32 ShopUpgradePrice;

	TArray<int32> ShopCards;

	bool ShopFrozen = false;

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_ShopTier();

};
