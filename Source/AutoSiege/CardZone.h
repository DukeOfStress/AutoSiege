#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardZone.generated.h"

UENUM(BlueprintType)
enum EZoneType
{
	OpponentBoard,
	PlayerBoard,
	PlayerHand
};

UCLASS()
class AUTOSIEGE_API ACardZone : public AActor
{

	GENERATED_BODY()
	
public:	
	ACardZone();

};
