#include "AutoSiegePlayerController.h"

#include "Components/TextBlock.h"

#include "AutoSiegeHUD.h"
#include "AutoSiegeUserWidget.h"
#include "Portrait.h"

AAutoSiegePlayerController::AAutoSiegePlayerController()
{

	bAutoManageActiveCameraTarget = false;
	bEnableClickEvents = true;
	bShowMouseCursor = true;

}

void AAutoSiegePlayerController::BeginPlay()
{

	Super::BeginPlay();

	GameState_Ref = GetWorld() != NULL ? GetWorld()->GetGameState<AAutoSiegeGameStateBase>() : NULL;
	PlayerState_Ref = GetPlayerState<AAutoSiegePlayerState>();

	if ( HasAuthority() )
		return;
	
	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Board.Board'")));
	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if ( !SpawnActor )
		return;

	UClass* SpawnClass = SpawnActor->StaticClass();
	if ( SpawnActor == NULL )
		return;

	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PlayerBoard = GetWorld()->SpawnActor<ABoard>(GeneratedBP->GeneratedClass, Location, Rotation, SpawnParams);
	SetViewTarget(PlayerBoard);

}

bool AAutoSiegePlayerController::Server_PlayerReady_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_PlayerReady_Implementation()
{
	GameState_Ref->NumberOfReadyPlayers++;
}
