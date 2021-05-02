#pragma once

#include "CoreMinimal.h"

#include "FPlayerCard.h"
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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ShopUpgradePrice)
	int32 ShopUpgradePrice;

	TArray<FPlayerCard> ShopCards;

	bool ShopFrozen = false;

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_ShopTier();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_ShopUpgradePrice();

};
