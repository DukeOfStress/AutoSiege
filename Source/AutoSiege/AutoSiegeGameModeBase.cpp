#include "AutoSiegeGameModeBase.h"
#include "AutoSiegeGameStateBase.h"

AAutoSiegeGameModeBase::AAutoSiegeGameModeBase(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	GameStateClass = AAutoSiegeGameStateBase::StaticClass();
	PlayerControllerClass = AAutoSiegePlayerController::StaticClass();
	PlayerStateClass = AAutoSiegePlayerState::StaticClass();
	
	static ConstructorHelpers::FObjectFinder<UDataTable> HeroDataObject(TEXT("DataTable'/Game/Data/Hero_DataTable.Hero_DataTable'"));
	if (HeroDataObject.Succeeded())
	{
		HeroDataTable = HeroDataObject.Object;
	}

	bPauseable = false;

	NumberOfConnectedPlayers = 0;

	CurrentStage = GameStage::PlayerJoin;
}

void AAutoSiegeGameModeBase::BeginPlay()
{

	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameMode::BeginPlay"));

	HeroPool = HeroDataTable->GetRowNames();
	// Shuffle HeroPool
	for (int32 i = HeroPool.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % HeroPool.Num();
		FName temp = HeroPool[i];
		HeroPool[i] = HeroPool[j];
		HeroPool[j] = temp;
	}

}

void AAutoSiegeGameModeBase::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);

	if( PlayerControllerArray.Num() <= MAX_NUM_PLAYERS ){
		PlayerControllerArray.AddUnique((AAutoSiegePlayerController*)NewPlayer);
		
		auto ps = (AAutoSiegePlayerState*)(NewPlayer->PlayerState);
		PlayerStateArray.AddUnique(ps);

		ps->PlayerIndex = PlayerControllerArray.Num() - 1;
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GameMode::PostLogin - %d"), ps->PlayerIndex));

		// Dish out heroes from the pool into the PlayerState
		for (int i = NumberOfConnectedPlayers; i < NumberOfConnectedPlayers + 3; i++)
		{
			ps->AvailableHeroes.Add(HeroPool[i]);
		}
		NumberOfConnectedPlayers++;

		if (PlayerControllerArray.Num() == MAX_NUM_PLAYERS)
		{
			CurrentStage = GameStage::HeroSelect;
		}

	}

}
