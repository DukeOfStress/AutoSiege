#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Portrait.generated.h"

UCLASS()
class AUTOSIEGE_API APortrait : public AActor
{

	GENERATED_BODY()
	
public:	
	APortrait();

	UFUNCTION(BlueprintImplementableEvent, Category = "Portrait", meta = (DisplayName = "OnUpdatePortrait"))
	void ReceiveOnUpdatePortrait(FName HeroName);

	UFUNCTION(BlueprintImplementableEvent, Category = "Portrait", meta = (DisplayName = "OnUpdateHealth"))
	void ReceiveOnUpdateHealth();

};
