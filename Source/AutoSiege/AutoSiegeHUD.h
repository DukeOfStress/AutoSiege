#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "AutoSiegeHUD.generated.h"

UCLASS()
class AUTOSIEGE_API AAutoSiegeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAutoSiegeHUD();

	virtual void BeginPlay() override;
	
	UPROPERTY()
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* CurrentWidget;

};
