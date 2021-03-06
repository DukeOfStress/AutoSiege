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

void AAutoSiegePlayerController::SelectHero(APortrait* hero)
{
	for (int i = 0; i < HeroSelectPortraits.Num(); i++)
	{
		if (HeroSelectPortraits[i] == hero)
		{
			HeroPortrait = hero;
			continue;
		}

		GetWorld()->DestroyActor(HeroSelectPortraits[i]);
	}

	HeroSelectPortraits.Reset();

	Server_PlayerReady(hero->Name);
}


bool AAutoSiegePlayerController::Server_PlayerReady_Validate(FName HeroName)
{
	return true;
}

void AAutoSiegePlayerController::Server_PlayerReady_Implementation(FName HeroName)
{
	if (PlayerReadyCheck[PlayerState_Ref->PlayerIndex])
		return;

	PlayerReadyCheck[PlayerState_Ref->PlayerIndex] = true;
	GameState_Ref->NumberOfReadyPlayers++;

	GameState_Ref->Heroes[PlayerState_Ref->PlayerIndex] = HeroName;

	if (GameState_Ref->NumberOfReadyPlayers == GameState_Ref->TotalNumberOfPlayers)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "All players are ready!");
	
		// TODO: Trigger next game state [SHOP]
		GameState_Ref->CurrentStage = GameStage::Shop;
	}
}

bool AAutoSiegePlayerController::Server_RefreshShop_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_RefreshShop_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

bool AAutoSiegePlayerController::Server_UpgradeShop_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_UpgradeShop_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

bool AAutoSiegePlayerController::Server_FreezeShop_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_FreezeShop_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

bool AAutoSiegePlayerController::Server_BuyCard_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_BuyCard_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

bool AAutoSiegePlayerController::Server_SellCard_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_SellCard_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

bool AAutoSiegePlayerController::Server_PlayCard_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_PlayCard_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

bool AAutoSiegePlayerController::Server_ReorderCards_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_ReorderCards_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}

bool AAutoSiegePlayerController::Server_CastHeroAbility_Validate()
{
	return true;
}

void AAutoSiegePlayerController::Server_CastHeroAbility_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Server!");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Client!");
	}
}
