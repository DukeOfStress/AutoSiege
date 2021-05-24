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
	GameState_Ref->CurrentStage = GameStage::HeroSelect;

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
	GameState_Ref->RoundTimer = 20.0f;
	GetWorldTimerManager().SetTimer(
		PlayerReadyTimerHandle, 
		this, 
		&AAutoSiegeGameModeBase::PlayerReadyTimerCountdown,
		1.0f,
		true,
		2.0f
	);

	GameState_Ref->MatchUps.Reset();

	TArray<int32> AvailableHeroes;
	bool PlayerHasDied = false;
	int32 HighestDeadPlayerRank = 9999;
	int32 HighestDeadPlayerId = 9999;
	for (auto PlayerState : PlayerStateArray)
	{
		if (PlayerState->Health > 0)
		{
			AvailableHeroes.Add(PlayerState->PlayerIndex);
		}
		else
		{
			if (PlayerHasDied)
			{
				if (PlayerState->Rank < HighestDeadPlayerRank)
				{
					HighestDeadPlayerId = PlayerState->PlayerIndex;
					HighestDeadPlayerRank = PlayerState->Rank;
				}
			}
			else
			{
				PlayerHasDied = true;
				HighestDeadPlayerId = PlayerState->PlayerIndex;
				HighestDeadPlayerRank = PlayerState->Rank;
			}
		}
	}

	if (AvailableHeroes.Num() % 2 != 0)
	{
		AvailableHeroes.Add(HighestDeadPlayerId);
	}
	
	while (AvailableHeroes.Num() > 0)
	{
		FMatchUp MatchUp;

		int32 RandomIndex = FMath::RandRange(0, AvailableHeroes.Num() - 1);
		MatchUp.Player1 = AvailableHeroes[RandomIndex];
		AvailableHeroes.RemoveAt(RandomIndex);

		RandomIndex = FMath::RandRange(0, AvailableHeroes.Num() - 1);
		MatchUp.Player2 = AvailableHeroes[RandomIndex];
		AvailableHeroes.RemoveAt(RandomIndex);

		GameState_Ref->MatchUps.Add(MatchUp);
	}

	int32 RoundGold = 2 + GameState_Ref->RoundNumber;
	if (RoundGold > 10)
		RoundGold = 10;

	RoundGold = 10;
	
	for (auto PlayerController : PlayerControllerArray)
	{
		auto PlayerCards = PlayerController->RefreshShopCards();

		int32 NextOpponent = 9999;
		for (auto MatchUp : GameState_Ref->MatchUps)
		{
			if (MatchUp.Player1 == PlayerController->PlayerState_Ref->PlayerIndex)
				NextOpponent = MatchUp.Player2;

			if (MatchUp.Player2 == PlayerController->PlayerState_Ref->PlayerIndex)
				NextOpponent = MatchUp.Player1;
		}

		PlayerController->PlayerState_Ref->Gold = RoundGold;
		PlayerController->Client_BeginShop(RoundGold, PlayerCards, NextOpponent);
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

void AAutoSiegeGameModeBase::ReturnCardsToPool(const TArray<FPlayerCard> PlayerCards)
{
	for (auto PlayerCard: PlayerCards)
	{
		CardPool[PlayerCard.BaseCardID / 512].Add(PlayerCard.BaseCardID);
	}
}

void AAutoSiegeGameModeBase::TriggerBattlePhase()
{
	GameState_Ref->CurrentStage = GameStage::Battle;
	GetWorldTimerManager().ClearTimer(PlayerReadyTimerHandle);

	TMap<int32,FBattle> Battles;
	TMap<int32,FBattleOpponent> BattleOpponents;
	for (auto MatchUp : GameState_Ref->MatchUps)
	{
		BattleOpponents.Add(MatchUp.Player1, LoadBattleOpponent(MatchUp.Player2));
		BattleOpponents.Add(MatchUp.Player2, LoadBattleOpponent(MatchUp.Player1));
		
		auto Battle = AutoBattle(
			PlayerStateArray[MatchUp.Player1],
			PlayerStateArray[MatchUp.Player2]
		);
		
		Battles.Add(MatchUp.Player1, Battle);
		Battles.Add(MatchUp.Player2, Battle);
	}
	
	for (auto PlayerController : PlayerControllerArray)
	{
		PlayerController->Client_ShowBattle(
			BattleOpponents[PlayerController->PlayerState_Ref->PlayerIndex],
			Battles[PlayerController->PlayerState_Ref->PlayerIndex]
		);
	}
}


FBattle AAutoSiegeGameModeBase::AutoBattle(AAutoSiegePlayerState* PS1, AAutoSiegePlayerState* PS2)
{
	FBattle Battle = {};

	int32 Player1Index = 9999;
	int32 Player2Index = 9999;

	bool IsPlayer1Turn = FMath::RandBool();

	TArray<FPlayerCard> Player1Cards(PS1->BoardCards);
	TArray<FPlayerCard> Player2Cards(PS2->BoardCards);
	
	bool Player1HasLivingCards = PlayerHasLivingCards(Player1Cards);
	bool Player2HasLivingCards = PlayerHasLivingCards(Player2Cards);

	while (Player1HasLivingCards && Player2HasLivingCards)
	{
		if (IsPlayer1Turn)
		{
			Player1Index = GetNextLivingAttacker(Player1Cards, Player1Index);
			const int32 DefenderIndex = GetRandomLivingCard(Player2Cards);

			Player1Cards[Player1Index].Health -= Player2Cards[DefenderIndex].Power;
			Player2Cards[DefenderIndex].Health -= Player1Cards[Player1Index].Power;

			FBattleAction BattleAction = {};
			BattleAction.Type = CardAttacks;
			BattleAction.CurrentPlayer = PS1->PlayerIndex;
			BattleAction.AttackerUID = Player1Cards[Player1Index].UID;
			BattleAction.DefenderUID = Player2Cards[DefenderIndex].UID;
			BattleAction.NewAttackerHealth = Player1Cards[Player1Index].Health;
			BattleAction.NewDefenderHealth = Player2Cards[DefenderIndex].Health;
			Battle.Actions.Add(BattleAction);

			IsPlayer1Turn = false;
		}
		else
		{
			Player2Index = GetNextLivingAttacker(Player2Cards, Player2Index);
			const int32 DefenderIndex = GetRandomLivingCard(Player1Cards);

			Player1Cards[DefenderIndex].Health -= Player2Cards[Player2Index].Power;
			Player2Cards[Player2Index].Health -= Player1Cards[DefenderIndex].Power;

			FBattleAction BattleAction = {};
			BattleAction.Type = CardAttacks;
			BattleAction.CurrentPlayer = PS2->PlayerIndex;
			BattleAction.AttackerUID = Player2Cards[Player2Index].UID;
			BattleAction.DefenderUID = Player1Cards[DefenderIndex].UID;
			BattleAction.NewAttackerHealth = Player2Cards[Player2Index].Health;
			BattleAction.NewDefenderHealth = Player1Cards[DefenderIndex].Health;
			Battle.Actions.Add(BattleAction);

			IsPlayer1Turn = true;	
		}

		Player1HasLivingCards = PlayerHasLivingCards(Player1Cards);
		Player2HasLivingCards = PlayerHasLivingCards(Player2Cards);
	}

	// TODO: Log the winner and take health from the loser.
	if (!Player1HasLivingCards && !Player2HasLivingCards)
	{
		// It's a draw
		Battle.IsDraw = true;
	}
	else if (!Player1HasLivingCards)
	{
		// Player2 Won
		PS1->Health -= 3;
		Battle.IsDraw = false;
		Battle.LosingPlayer = PS1->PlayerIndex;
		Battle.NewLosingPlayerHealth = PS1->Health;
	}
	else if (!Player2HasLivingCards)
	{
		// Player1 Won
		PS2->Health -= 3;
		Battle.IsDraw = false;
		Battle.LosingPlayer = PS2->PlayerIndex;
		Battle.NewLosingPlayerHealth = PS2->Health;
	}

	return Battle; 
}

bool AAutoSiegeGameModeBase::PlayerHasLivingCards(TArray<FPlayerCard> PlayerCards)
{
	for (auto Card : PlayerCards)
	{
		if (Card.Health > 0)
			return true;
	}

	return false;
}

int32 AAutoSiegeGameModeBase::GetNextLivingAttacker(TArray<FPlayerCard> PlayerCards, int32 PreviousIndex)
{
	while(true)
	{
		PreviousIndex++;
		if (PreviousIndex >= PlayerCards.Num())
			PreviousIndex = 0;

		if (PlayerCards[PreviousIndex].Health > 0)
			return PreviousIndex;
	}
}

int32 AAutoSiegeGameModeBase::GetRandomLivingCard(TArray<FPlayerCard> PlayerCards)
{
	TArray<int32> Indexes;
	for (int32 i = 0; i < PlayerCards.Num(); i++)
	{
		if (PlayerCards[i].Health > 0)
		{
			Indexes.Add(i);
		}
	}

	const int32 RandomIndex = FMath::RandRange(0, Indexes.Num() - 1);
	return Indexes[RandomIndex];
}

FBattleOpponent AAutoSiegeGameModeBase::LoadBattleOpponent(const int32 PlayerIndex)
{
	FBattleOpponent Opponent;
	Opponent.ID = PlayerIndex;
	Opponent.Hero = PlayerStateArray[PlayerIndex]->Hero;
	Opponent.StartingHealth = PlayerStateArray[PlayerIndex]->Health;
	Opponent.Cards = PlayerStateArray[PlayerIndex]->BoardCards;

	return Opponent;
}


int32 AAutoSiegeGameModeBase::GenerateUID()
{
	return UIDCounter++;
}


void AAutoSiegeGameModeBase::PlayerReadyTimerCountdown()
{
	GameState_Ref->RoundTimer--;

	if (GameState_Ref->RoundTimer >= 0.f)
		return;

	switch (GameState_Ref->CurrentStage)
	{
		case HeroSelect:
			{
				AllowPlayerReady = false;

				for (int32 i = 0; i < GameState_Ref->TotalNumberOfPlayers; i++)
				{
					if (GameState_Ref->Heroes[i].IsNone())
					{
						// TODO: Do we want to randomize this? Or always pick the first?
						const FName SelectedHero = HeroPool[i * 3];
						GameState_Ref->Heroes[i] = SelectedHero;

						const FHero* Hero = HeroDataTable->FindRow<FHero>(SelectedHero, "");
				
						PlayerControllerArray[i]->PlayerState_Ref->Health = Hero->Health;
						PlayerControllerArray[i]->Client_HeroApproved(SelectedHero, Hero->Health);
					}
				}

				CheckAllPlayersReady();
			}
		break;
		case Shop:
			{
				TriggerBattlePhase();
			}
		break;
		case Battle:
			{
				
			}
		break;
		default:
			break;
	}
}
