#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Engine/DataTable.h"

#include "AutoSiegePlayerController.h"
#include "AutoSiegePlayerState.h"

#include "AutoSiegeGameModeBase.generated.h"

UENUM()
enum GameStage
{
	PlayerJoin,
	HeroSelect
};


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
};

USTRUCT(BlueprintType)
struct FCard : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;
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
	static const int MAX_NUM_PLAYERS = 3;
	//static const float SHOP_ROUND_TIME_SECONDS = 120.f;

	TArray<AAutoSiegePlayerController*> PlayerControllerArray;
	TArray<AAutoSiegePlayerState*> PlayerStateArray;

private:
	UDataTable* HeroDataTable;
	TArray<FName> HeroPool;
	int NumberOfConnectedPlayers; // Kinda duplicated by PlayerControllerArray.Num() - 1

	GameStage CurrentStage;

};
