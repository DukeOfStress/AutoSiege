#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "AutoSiegeHUD.generated.h"

UCLASS()
class AUTOSIEGE_API AAutoSiegeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAutoSiegeHUD();

	//virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Network")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Network")
	class UUserWidget* CurrentWidget;
};
