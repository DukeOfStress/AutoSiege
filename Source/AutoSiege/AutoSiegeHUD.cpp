#include "AutoSiegeHUD.h"
#include "UObject/ConstructorHelpers.h"

AAutoSiegeHUD::AAutoSiegeHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ConnectedPlayersObj(TEXT("WidgetBlueprint'/Game/UI/BP_AutoSiegeUserWidget'"));
	HUDWidgetClass = ConnectedPlayersObj.Class;
}

void AAutoSiegeHUD::BeginPlay()
{
	Super::BeginPlay();

	if ( HUDWidgetClass == nullptr )
		return;

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

	if ( CurrentWidget )
		CurrentWidget->AddToViewport();
}
