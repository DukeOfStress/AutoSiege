#include "AutoSiegePlayerController.h"
#include "AutoSiegeHUD.h"
#include "Components/TextBlock.h"
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

void AAutoSiegePlayerController::InitHeroSelect()
{
	if (!HasAuthority() && PlayerState_Ref != NULL && PlayerState_Ref->AvailableHeroes.Num() == 3)
	{
		UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Portrait.Portrait'")));
		UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
		if (!SpawnActor) return;

		UClass* SpawnClass = SpawnActor->StaticClass();
		if (SpawnActor == NULL) return;

		UWorld* World = GetWorld();

		for (int i = 0; i < PlayerState_Ref->AvailableHeroes.Num(); i++)
		{
			FVector Location(400.0f * i - 400.f, 0.0f, 1000.0f);
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			APortrait* portrait = World->SpawnActor<APortrait>(GeneratedBP->GeneratedClass, Location, Rotation, SpawnParams);
			portrait->ReceiveOnUpdatePortrait(PlayerState_Ref->AvailableHeroes[i]);
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("InitHeroSelect - %d"), PlayerState_Ref->PlayerIndex));
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