#include "AutoSiegePlayerController.h"

AAutoSiegePlayerController::AAutoSiegePlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void AAutoSiegePlayerController::BeginPlay()
{

	Super::BeginPlay();

	GameState_Ref = GetWorld() != NULL ? GetWorld()->GetGameState<AAutoSiegeGameStateBase>() : NULL;
	PlayerState_Ref = GetPlayerState<AAutoSiegePlayerState>();

	//if( HasAuthority() ){
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerController::BeginPlay"));
	//}
	//
	//TArray<UCameraComponent*> CameraComps;
	//PlayerBoard->GetComponents<UCameraComponent>(CameraComps);

	//if (PlayerState_Ref->PlayerIndex != NULL)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PlayerController::BeginPlay - %d"), PlayerState_Ref->PlayerIndex));
	//}
	
	if ( !HasAuthority() )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Client - PlayerController::BeginPlay"));

		int r = rand();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Rand - %d"), r));
		
		if ( r%2 == 0 ) // PlayerState_Ref->PlayerIndex == 1	This is probably not replicated, and causes a crash
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Banana"));
			auto pb = GetWorld() != NULL ? GetWorld()->SpawnActor<ABoard>() : NULL;
			SetViewTarget(pb);
		}
	}



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