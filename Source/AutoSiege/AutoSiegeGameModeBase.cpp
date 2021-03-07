#include "AutoSiegeGameModeBase.h"

#include "AutoSiegeHUD.h"

AAutoSiegeGameModeBase::AAutoSiegeGameModeBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	GameStateClass = AAutoSiegeGameStateBase::StaticClass();
	PlayerControllerClass = AAutoSiegePlayerController::StaticClass();
	PlayerStateClass = AAutoSiegePlayerState::StaticClass();
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
		int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % HeroPool.Num();
		FName temp = HeroPool[i];
		HeroPool[i] = HeroPool[j];
		HeroPool[j] = temp;
	}

	TArray<FName> CardIDs = CardDataTable->GetRowNames();
	for (int32 i = 0; i < CardIDs.Num(); i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Card found!");
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAutoSiegeGameModeBase::TimerCountdown, 1.0f, true, 2.0f);

}

void AAutoSiegeGameModeBase::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);

	if( PlayerControllerArray.Num() <= GameState_Ref->TotalNumberOfPlayers){
		PlayerControllerArray.AddUnique((AAutoSiegePlayerController*)NewPlayer);
		
		auto ps = (AAutoSiegePlayerState*)(NewPlayer->PlayerState);
		PlayerStateArray.AddUnique(ps);

		ps->PlayerIndex = PlayerControllerArray.Num() - 1;

		// Dish out heroes from the pool into the PlayerState
		for (int i = ps->PlayerIndex * 3; i < (ps->PlayerIndex * 3) + 3; i++)
		{
			ps->AvailableHeroes.Add(HeroPool[i]);
		}
		GameState_Ref->NumberOfConnectedPlayers++;

		if (PlayerControllerArray.Num() == GameState_Ref->TotalNumberOfPlayers)
		{
			GameState_Ref->CurrentStage = GameStage::HeroSelect;
		}

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
