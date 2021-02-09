#include "AutoSiegeGameStateBase.h"

#include "Net/UnrealNetwork.h"

#include "AutoSiegeHUD.h"
#include "AutoSiegeUserWidget.h"

void AAutoSiegeGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAutoSiegeGameStateBase, RoundTimer);
	//DOREPLIFETIME(AAutoSiegeGameStateBase, PlayerHealth);
	DOREPLIFETIME(AAutoSiegeGameStateBase, NumberOfReadyPlayers);
}

void AAutoSiegeGameStateBase::OnRep_RoundTimer()
{
	if (!HasAuthority())
	{
		AAutoSiegeHUD* hud = Cast<AAutoSiegeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		UAutoSiegeUserWidget* uw = (UAutoSiegeUserWidget*)hud->CurrentWidget;
		uw->UpdateRoundTimer();
	}
}

void AAutoSiegeGameStateBase::OnRep_NumberOfReadyPlayers()
{
	if (!HasAuthority())
	{
		AAutoSiegeHUD* hud = Cast<AAutoSiegeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		UAutoSiegeUserWidget* uw = (UAutoSiegeUserWidget*)hud->CurrentWidget;
		uw->UpdatePlayersReady();
	}
}