#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/GameModeBase.h"
#include "AutoSiegeGameStateBase.h"
#include "AutoSiegePlayerController.h"
#include "AutoSiegePlayerState.h"
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
	UTexture* Texture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
};

USTRUCT(BlueprintType)
struct FCardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Power;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
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

	UPROPERTY()
	UDataTable* HeroDataTable;
	
	void CheckAllPlayersReady();
	void TriggerShopPhase();

	TArray<FPlayerCard> GetCardsFromPool(int32 MaxTier,  int32 NumberOfCards);
	void ReturnCardsToPool(const TArray<FPlayerCard> PlayerCards);

	void TriggerBattlePhase();

	int32 GenerateUID();
	
private:
	TArray<FName> HeroPool;

	UPROPERTY()
	UDataTable* CardDataTable;
	TArray<TArray<int32>> CardPool;

	int32 UIDCounter = 0;

	void PlayerReadyTimerCountdown();

};
