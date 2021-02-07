#include "AutoSiegeHUD.h"
#include "UObject/ConstructorHelpers.h"

AAutoSiegeHUD::AAutoSiegeHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ConnectedPlayersObj(TEXT
	("/Game/UI/ConnectedPlayers_UI"));

	HUDWidgetClass = ConnectedPlayersObj.Class;
}

//void AAutoSiegeHUD::DrawHUD()
//{
//	Super::DrawHUD();
//
//
//}

void AAutoSiegeHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}