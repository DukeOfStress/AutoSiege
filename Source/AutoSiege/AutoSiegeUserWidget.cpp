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
	if (RoundTimer_Text)
	{
		AAutoSiegeGameStateBase* gs = (AAutoSiegeGameStateBase*)(GetWorld()->GetGameState());

		FFormatOrderedArguments Args;
		Args.Add(gs->RoundTimer);

		RoundTimer_Text->SetText(FText::Format(
			NSLOCTEXT("AutoSiege", "RoundTimer", "{0}"),
			Args
		));
	}
}

void UAutoSiegeUserWidget::UpdatePlayersReady()
{
	if (PlayersReady_Text)
	{
		AAutoSiegeGameStateBase* gs = (AAutoSiegeGameStateBase*)(GetWorld()->GetGameState());

		FFormatOrderedArguments Args;
		Args.Add(gs->NumberOfReadyPlayers);
		Args.Add(gs->TotalNumberOfPlayers);

		PlayersReady_Text->SetText(FText::Format(
			NSLOCTEXT("AutoSiege", "NumberOfReadyPlayers", "{0}/{1} Players Ready"),
			Args
		));
	}
}