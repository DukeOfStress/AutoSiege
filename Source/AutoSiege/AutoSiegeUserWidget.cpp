#include "AutoSiegeUserWidget.h"
#include "Components/TextBlock.h"
#include "AutoSiegeGameStateBase.h"

void UAutoSiegeUserWidget::NativeConstruct()
{

	Super::NativeConstruct();

	UpdatePlayersReady();

}

void UAutoSiegeUserWidget::UpdateRoundTimer()
{

	if (!RoundTimer_Text)
		return;
	
	AAutoSiegeGameStateBase* gs = (AAutoSiegeGameStateBase*)(GetWorld()->GetGameState());

	FFormatOrderedArguments Args;
	Args.Add(gs->RoundTimer);

	RoundTimer_Text->SetText(FText::Format(
		NSLOCTEXT("AutoSiege", "RoundTimer", "{0}"),
		Args
	));

}

void UAutoSiegeUserWidget::UpdatePlayersReady()
{

	if (!PlayersReady_Text)
		return;
	
	AAutoSiegeGameStateBase* gs = (AAutoSiegeGameStateBase*)(GetWorld()->GetGameState());

	FFormatOrderedArguments Args;
	Args.Add(gs->NumberOfReadyPlayers);
	Args.Add(gs->TotalNumberOfPlayers);

	PlayersReady_Text->SetText(FText::Format(
		NSLOCTEXT("AutoSiege", "NumberOfReadyPlayers", "{0}/{1} Players Ready"),
		Args
	));

}

void UAutoSiegeUserWidget::UpdateShopUpgradeCost(int32 ShopUpgradeCost)
{

	if (!ShopUpgradeCost_Text)
		return;

	FFormatOrderedArguments Args;
	Args.Add(ShopUpgradeCost);

	ShopUpgradeCost_Text->SetText(FText::Format(
		NSLOCTEXT("AutoSiege", "ShopUpgradeCost", "{0}"),
		Args
	));
	
}