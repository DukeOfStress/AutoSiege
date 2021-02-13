#include "AutoSiegePlayerState.h"
#include "AutoSiegePlayerController.h"
#include "Portrait.h"

AAutoSiegePlayerState::AAutoSiegePlayerState() 
{
    AvailableHeroes = {};
}

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
    DOREPLIFETIME(AAutoSiegePlayerState, AvailableHeroes);
    DOREPLIFETIME(AAutoSiegePlayerState, ChosenHero);

}

void AAutoSiegePlayerState::OnRep_AvailableHeroes()
{
	AAutoSiegePlayerController* playerController = GetWorld()->GetFirstPlayerController<AAutoSiegePlayerController>();

	if (GetOwner() != playerController)
		return;
	
	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Portrait.Portrait'")));
	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if ( !SpawnActor )
		return;

	UClass* SpawnClass = SpawnActor->StaticClass();
	if ( SpawnActor == NULL )
		return;

	UWorld* World = GetWorld();

	for (int i = 0; i < AvailableHeroes.Num(); i++)
	{
		FVector Location(400.0f * i - 400.f, 0.0f, 1000.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		APortrait* portrait = World->SpawnActor<APortrait>(GeneratedBP->GeneratedClass, Location, Rotation, SpawnParams);
		portrait->OnUpdatePortrait(AvailableHeroes[i]);
		playerController->HeroSelectPortraits.Add(portrait);
	}

}