#include "AutoSiegeGameModeBase.h"

#include "AutoSiegeHUD.h"

AAutoSiegeGameModeBase::AAutoSiegeGameModeBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	GameStateClass = AAutoSiegeGameStateBase::StaticClass();
	PlayerControllerClass = AAutoSiegePlayerController::StaticClass();
	PlayerStateClass = AAutoSiegePlayerState::StaticClass();
	HUDClass = AAutoSiegeHUD::StaticClass();

	// Override C++ PlayerController with the Blueprint
	ConstructorHelpers::FClassFinder<AAutoSiegePlayerController> BlueprintPlayerController(TEXT("Class'/Game/BP_AutoSiegePlayerController.BP_AutoSiegePlayerController_C'"));
	if (BlueprintPlayerController.Class != NULL)
	{
		PlayerControllerClass = BlueprintPlayerController.Class;
	}
	
	static ConstructorHelpers::FObjectFinder<UDataTable> HeroDataObject(TEXT("DataTable'/Game/Data/Hero_DataTable.Hero_DataTable'"));
	if (HeroDataObject.Succeeded())
	{
		HeroDataTable = HeroDataObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> CardDataObject(TEXT("DataTable'/Game/Data/CardData_DataTable.CardData_DataTable'"));
	if (CardDataObject.Succeeded())
	{
		CardDataTable = CardDataObject.Object;
	}

	bPauseable = false;

}

void AAutoSiegeGameModeBase::BeginPlay()
{

	Super::BeginPlay();

	GameState_Ref = GetGameState<AAutoSiegeGameStateBase>();
	GameState_Ref->CurrentStage = GameStage::PlayerJoin;

	HeroPool = HeroDataTable->GetRowNames();
	// Shuffle HeroPool
	for (int32 i = HeroPool.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % HeroPool.Num();
		FName temp = HeroPool[i];
		HeroPool[i] = HeroPool[j];
		HeroPool[j] = temp;
	}

	// Create an empty array in CardPool for all 6 tiers.
	for (int32 i = 0; i < 6; i++)
	{
		CardPool.Add({});
	}

	TArray<FName> CardIDs = CardDataTable->GetRowNames();
	TArray<int32> NumberOfCopies = { 18, 15, 13, 11, 9, 6 };
	for (int32 i = 0; i < CardIDs.Num(); i++)
	{
		// Cast CardID to int
		int CardID = FCString::Atoi(*(CardIDs[i].ToString()));
		int CardTier = CardID / 512;

		if (CardTier < 0 || CardTier > 5)
			continue;

		for (int32 j = 0; j < NumberOfCopies[CardTier]; j++)
		{
			CardPool[CardTier].Add(CardID);
		}
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAutoSiegeGameModeBase::TimerCountdown, 1.0f, true, 2.0f);

}

void AAutoSiegeGameModeBase::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);

	if (PlayerControllerArray.Num() > GameState_Ref->TotalNumberOfPlayers)
		return;

	auto pc = (AAutoSiegePlayerController*)NewPlayer;
	PlayerControllerArray.AddUnique(pc);
		
	auto ps = (AAutoSiegePlayerState*)(pc->PlayerState);
	PlayerStateArray.AddUnique(ps);

	// Set the PlayerState defaults
	ps->PlayerIndex = PlayerControllerArray.Num() - 1;
	ps->Gold = 200; //TODO: Starting gold should be 3
	ps->ShopUpgradePrice = 5;
	ps->ShopTier = 1;

	// Dish out heroes from the pool into the PlayerState
	TArray<FName> Heroes;
	for (int i = ps->PlayerIndex * 3; i < (ps->PlayerIndex * 3) + 3; i++)
	{
		Heroes.Add(HeroPool[i]);
	}
	GameState_Ref->NumberOfConnectedPlayers++;

	pc->Client_PresentHeroes(Heroes);

}

void AAutoSiegeGameModeBase::CheckAllPlayersReady()
{
	if (GameState_Ref->NumberOfReadyPlayers < GameState_Ref->TotalNumberOfPlayers)
		return;

	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "All players are ready!");
	GameState_Ref->CurrentStage = GameStage::Shop;

	// TODO: Multicast switch to shop

}

TArray<int32> AAutoSiegeGameModeBase::GetCardsFromPool(int32 MaxTier, int32 NumberOfCards)
{
	TArray<int32> CardIDs = {};

	if (MaxTier < 0 || MaxTier > 5)
		return CardIDs;

	TArray<int32> TempPool = {};
	for (int32 i = 0; i <= MaxTier; i++)
	{
		for (int32 j = 0; j < CardPool[i].Num(); j++)
		{
			TempPool.Add(CardPool[i][j]);
		}
	}

	for (int32 i = 0; i < NumberOfCards; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, TempPool.Num() - 1);
		CardIDs.Add(TempPool[RandomIndex]);
		TempPool.RemoveAt(RandomIndex);
	}

	return CardIDs;
}

void AAutoSiegeGameModeBase::ReturnCardsToPool(TArray<int32> CardIDs)
{
	for (int32 i = 0; i < CardIDs.Num(); i++)
	{
		CardPool[CardIDs[i] / 512].Add(CardIDs[i]);
	}
}

void AAutoSiegeGameModeBase::TimerCountdown()
{
	GameState_Ref->RoundTimer--;

	if (GameState_Ref->RoundTimer <= 0.f)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}
