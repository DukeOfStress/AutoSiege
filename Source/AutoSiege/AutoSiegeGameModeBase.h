#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Engine/DataTable.h"

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
	//static const float SHOP_ROUND_TIME_SECONDS = 120.f;

	TArray<AAutoSiegePlayerController*> PlayerControllerArray;
	TArray<AAutoSiegePlayerState*> PlayerStateArray;
	AAutoSiegeGameStateBase* GameState_Ref;

private:
	UDataTable* HeroDataTable;
	TArray<FName> HeroPool;

};
