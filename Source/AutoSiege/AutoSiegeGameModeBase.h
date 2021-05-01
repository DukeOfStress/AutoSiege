#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/GameModeBase.h"
#include "AutoSiegeGameStateBase.h"
#include "AutoSiegePlayerController.h"
#include "AutoSiegePlayerState.h"
#include "Card.h"
#include "AutoSiegeGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FHero : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture* Texture;
};

USTRUCT(BlueprintType)
struct FCardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;
};

USTRUCT(BlueprintType)
struct FPlayerCard
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 UID;

	UPROPERTY(BlueprintReadOnly)
	int32 BaseCardID;

	UPROPERTY(BlueprintReadOnly)
	int32 Power;

	UPROPERTY(BlueprintReadOnly)
	int32 Health;

	UPROPERTY(BlueprintReadWrite)
	ACard* CardActor;
};

USTRUCT(BlueprintType)
struct FPlayerHero
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName HeroName;

	UPROPERTY(BlueprintReadOnly)
	int32 Health;
};

UCLASS()
class AUTOSIEGE_API AAutoSiegeGameModeBase : public AGameModeBase
{

	GENERATED_BODY()

public:
	AAutoSiegeGameModeBase(const class FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	UPROPERTY()
	AAutoSiegeGameStateBase* GameState_Ref;

	UPROPERTY()
	TArray<AAutoSiegePlayerController*> PlayerControllerArray;

	UPROPERTY()
	TArray<AAutoSiegePlayerState*> PlayerStateArray;

	FTimerHandle PlayerReadyTimerHandle;
	bool AllowPlayerReady = true;

	void CheckAllPlayersReady();
	void TriggerShopPhase();

	TArray<int32> GetCardsFromPool(int32 MaxTier, int32 NumberOfCards);
	void ReturnCardsToPool(TArray<int32> CardIDs);

private:
	UPROPERTY()
	UDataTable* HeroDataTable;
	TArray<FName> HeroPool;

	UPROPERTY()
	UDataTable* CardDataTable;
	TArray<TArray<int32>> CardPool;

	void PlayerReadyTimerCountdown();

};
