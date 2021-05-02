#include "AutoSiegeGameModeBase.h"

#include <string>

#include "AutoSiegeHUD.h"

AAutoSiegeGameModeBase::AAutoSiegeGameModeBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AAutoSiegeGameStateBase::StaticClass();
	// Override C++ GameStateBase with the Blueprint
	const ConstructorHelpers::FClassFinder<AAutoSiegeGameStateBase> BlueprintGameStateBase(TEXT("Class'/Game/BP_AutoSiegeGameStateBase.BP_AutoSiegeGameStateBase_C'"));
	if (BlueprintGameStateBase.Class != nullptr)
	{
		GameStateClass = BlueprintGameStateBase.Class;
	}	

	PlayerControllerClass = AAutoSiegePlayerController::StaticClass();
	// Override C++ PlayerController with the Blueprint
	const ConstructorHelpers::FClassFinder<AAutoSiegePlayerController> BlueprintPlayerController(TEXT("Class'/Game/BP_AutoSiegePlayerController.BP_AutoSiegePlayerController_C'"));
	if (BlueprintPlayerController.Class != nullptr)
	{
		PlayerControllerClass = BlueprintPlayerController.Class;
	}

	PlayerStateClass = AAutoSiegePlayerState::StaticClass();
	// Override C++ PlayerState with the Blueprint
	const ConstructorHelpers::FClassFinder<AAutoSiegePlayerState> BlueprintPlayerState(TEXT("Class'/Game/BP_AutoSiegePlayerState.BP_AutoSiegePlayerState_C'"));
	if (BlueprintPlayerState.Class != nullptr)
	{
		PlayerStateClass = BlueprintPlayerState.Class;
	}

	HUDClass = AAutoSiegeHUD::StaticClass();
	
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
		const int32 RandomIndex = FMath::FloorToInt(FMath::SRand() * (i + 1)) % HeroPool.Num();
		const FName Temp = HeroPool[i];
		HeroPool[i] = HeroPool[RandomIndex];
		HeroPool[RandomIndex] = Temp;
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
		const int CardTier = CardID / 512;

		if (CardTier < 0 || CardTier > 5)
			continue;

		for (int32 j = 0; j < NumberOfCopies[CardTier]; j++)
		{
			CardPool[CardTier].Add(CardID);
		}
	}

	GetWorldTimerManager().SetTimer(
		PlayerReadyTimerHandle, 
		this, 
		&AAutoSiegeGameModeBase::PlayerReadyTimerCountdown,
		1.0f,
		true,
		2.0f
	);

	GameState_Ref->Heroes.SetNum(GameState_Ref->TotalNumberOfPlayers);
}

void AAutoSiegeGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (PlayerControllerArray.Num() > GameState_Ref->TotalNumberOfPlayers)
		return;

	const auto PlayerController = static_cast<AAutoSiegePlayerController*>(NewPlayer);
	PlayerControllerArray.AddUnique(PlayerController);
		
	const auto PlayerState = static_cast<AAutoSiegePlayerState*>(PlayerController->PlayerState);
	PlayerStateArray.AddUnique(PlayerState);

	// Set the PlayerState defaults
	PlayerState->PlayerIndex = PlayerControllerArray.Num() - 1;
	PlayerState->Gold = 0;
	PlayerState->ShopUpgradePrice = 5;
	PlayerState->ShopTier = 1;

	TArray<FName> Heroes;
	for (int i = PlayerState->PlayerIndex * 3; i < (PlayerState->PlayerIndex * 3) + 3; i++)
	{
		Heroes.Add(HeroPool[i]);
	}

	PlayerController->Client_PresentHeroes(Heroes);
}

void AAutoSiegeGameModeBase::CheckAllPlayersReady()
{
	for (auto HeroName : GameState_Ref->Heroes)
	{
		if (HeroName.IsNone())
			return;
	}

	GetWorldTimerManager().ClearTimer(PlayerReadyTimerHandle);
	
	for (auto PlayerController : PlayerControllerArray)
	{
		const TArray<FName> Cards;
		PlayerController->Client_AllPlayersReady(GameState_Ref->Heroes);
	}

	// TODO: Remove if this is the only reference! (not sure yet)
	TriggerShopPhase();
}

void AAutoSiegeGameModeBase::TriggerShopPhase()
{
	GameState_Ref->CurrentStage = GameStage::Shop;

	int32 RoundGold = 2 + GameState_Ref->RoundNumber;
	if (RoundGold > 10)
		RoundGold = 10;

RoundGold = 10;
	
	for (auto PlayerController : PlayerControllerArray)
	{
		auto PlayerCards = PlayerController->RefreshShopCards();

		PlayerController->PlayerState_Ref->Gold = RoundGold;
		PlayerController->Client_BeginShop(RoundGold, PlayerCards);
	}
}

TArray<FPlayerCard> AAutoSiegeGameModeBase::GetCardsFromPool(const int32 MaxTier, const int32 NumberOfCards)
{
	TArray<FPlayerCard> PlayerCards;

	if (MaxTier < 0 || MaxTier > 5)
		return PlayerCards;

	TArray<int32> TempPool = {};
	for (int32 i = 0; i < MaxTier; i++)
	{
		for (int32 j = 0; j < CardPool[i].Num(); j++)
		{
			TempPool.Add(CardPool[i][j]);
		}
	}

	for (int32 i = 0; i < NumberOfCards; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, TempPool.Num() - 1);
		const int32 BaseCardID = TempPool[RandomIndex];
		const FName BaseCardName = static_cast<FName>(FString::FromInt(BaseCardID));

		const FCardData* BaseCardData = CardDataTable->FindRow<FCardData>(BaseCardName, "");
		
		FPlayerCard PlayerCard = {
			GenerateUID(),
			BaseCardID,
			BaseCardData->Name,
			BaseCardData->Power,
			BaseCardData->Health
		};
		PlayerCards.Add(PlayerCard);
		TempPool.RemoveAt(RandomIndex);
	}

	return PlayerCards;
}

void AAutoSiegeGameModeBase::ReturnCardsToPool(TArray<FPlayerCard> PlayerCards)
{
	for (auto PlayerCard: PlayerCards)
	{
		CardPool[PlayerCard.BaseCardID / 512].Add(PlayerCard.BaseCardID);
	}
}

int32 AAutoSiegeGameModeBase::GenerateUID()
{
	return UIDCounter++;
}


void AAutoSiegeGameModeBase::PlayerReadyTimerCountdown()
{
	GameState_Ref->RoundTimer--;

	if (GameState_Ref->RoundTimer <= 0.f)
	{
		AllowPlayerReady = false;

		for (int32 i = 0; i < GameState_Ref->TotalNumberOfPlayers; i++)
		{
			if (GameState_Ref->Heroes[i].IsNone())
			{
				// TODO: Do we want to randomize this? Or always pick the first?
				const FName SelectedHero = HeroPool[i * 3];
				GameState_Ref->Heroes[i] = SelectedHero;
				PlayerControllerArray[i]->Client_HeroApproved(SelectedHero);
			}
		}

		CheckAllPlayersReady();
	}
}
