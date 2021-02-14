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
	AAutoSiegePlayerState();

	UPROPERTY(Replicated)
	int PlayerIndex;

	UPROPERTY(ReplicatedUsing = OnRep_AvailableHeroes)
	TArray<FName> AvailableHeroes;

	UPROPERTY(ReplicatedUsing = OnRep_ShopCards)
	TArray<FName> ShopCards;

	UPROPERTY(Replicated)
	FName ChosenHero;

private:
	UFUNCTION()
	void OnRep_AvailableHeroes();

	UFUNCTION()
	void OnRep_ShopCards();

};
