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
	FString Description;
};

USTRUCT(BlueprintType)
struct FCardData : public FTableRowBase
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
	FTimerHandle TimerHandle;

	TArray<AAutoSiegePlayerController*> PlayerControllerArray;
	TArray<AAutoSiegePlayerState*> PlayerStateArray;
	AAutoSiegeGameStateBase* GameState_Ref;

private:
	UDataTable* HeroDataTable;
	TArray<FName> HeroPool;

	UDataTable* CardDataTable;
	TArray<TArray<FName>> CardPool;

	void TimerCountdown();

};
