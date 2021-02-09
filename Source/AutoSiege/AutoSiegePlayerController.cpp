#include "AutoSiegePlayerController.h"
#include "AutoSiegeHUD.h"
#include "Components/TextBlock.h"
#include "AutoSiegeUserWidget.h"

AAutoSiegePlayerController::AAutoSiegePlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void AAutoSiegePlayerController::BeginPlay()
{

	Super::BeginPlay();

	GameState_Ref = GetWorld() != NULL ? GetWorld()->GetGameState<AAutoSiegeGameStateBase>() : NULL;
	
	if ( !HasAuthority() )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Client - PlayerController::BeginPlay"));

		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;

		PlayerBoard = GetWorld()->SpawnActor<ABoard>(Location, Rotation, SpawnInfo);
		SetViewTarget(PlayerBoard);
	}

}

bool AAutoSiegePlayerController::Server_PlayerReady_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_PlayerReady_Implementation()
{
	GameState_Ref->NumberOfReadyPlayers++;
}















void AAutoSiegePlayerController::SetCardLocation( /*3DCard*/ AActor card, FVector holdLocation, FRotator rotation)
{
	UWorld* world = GetWorld();

	if (IsValid(&card))
	{
		card.SetActorLocation(FMath::VInterpTo(
			card.GetActorLocation(),
			holdLocation,
			world->GetDeltaSeconds(),
			10.0f
		));
	}

	if (enableInHandMovementRotation)
	{
		FVector rotationScale = (card.GetActorLocation() - holdLocation) / 5.0f;
		if (rotation.Yaw > 0.0f)
		{
			rotationScale.Y = rotationScale.Y * -1.0f;
		}
		else
		{
			rotationScale.X = rotationScale.X * -1.0f;
		}

		card.SetActorRotation(FMath::RInterpTo(
			card.GetActorRotation(),
			FRotator(rotationScale.Y, rotationScale.X, rotation.Yaw),
			world->GetDeltaSeconds(),
			5.0f
		));
	}
}