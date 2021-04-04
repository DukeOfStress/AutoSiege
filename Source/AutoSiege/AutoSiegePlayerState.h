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
	//AAutoSiegePlayerState();

	UPROPERTY(Replicated)
	int PlayerIndex;

	UPROPERTY(ReplicatedUsing = OnRep_ChosenHero)
	FName ChosenHero;

	UPROPERTY(ReplicatedUsing = OnRep_Gold)
	uint32 Gold; 

	UPROPERTY(ReplicatedUsing = OnRep_ShopCards)
	TArray<uint32> ShopCards;

	UPROPERTY(ReplicatedUsing = OnRep_ShopTier)
	uint32 ShopTier;

	UPROPERTY(ReplicatedUsing = OnRep_ShopUpgradePrice)
	uint32 ShopUpgradePrice;

private:

	UFUNCTION()
	void OnRep_ChosenHero();

	UFUNCTION()
	void OnRep_Gold();

	UFUNCTION()
	void OnRep_ShopCards();

	UFUNCTION()
	void OnRep_ShopTier();

	UFUNCTION()
	void OnRep_ShopUpgradePrice();

};
