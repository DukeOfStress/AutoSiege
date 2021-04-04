#include "AutoSiegeGameStateBase.h"

#include "Net/UnrealNetwork.h"

#include "AutoSiegeHUD.h"
#include "AutoSiegeUserWidget.h"

void AAutoSiegeGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAutoSiegeGameStateBase, RoundTimer);
	DOREPLIFETIME(AAutoSiegeGameStateBase, NumberOfReadyPlayers);
	DOREPLIFETIME(AAutoSiegeGameStateBase, Heroes);

}

void AAutoSiegeGameStateBase::OnRep_RoundTimer()
{

	if ( HasAuthority() )
		return;
	
	AAutoSiegeHUD* hud = Cast<AAutoSiegeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	UAutoSiegeUserWidget* uw = (UAutoSiegeUserWidget*)hud->CurrentWidget;
	uw->UpdateRoundTimer();
	
}

void AAutoSiegeGameStateBase::OnRep_NumberOfReadyPlayers()
{

	if (HasAuthority())
		return;

	AAutoSiegeHUD* hud = Cast<AAutoSiegeHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	UAutoSiegeUserWidget* uw = (UAutoSiegeUserWidget*)hud->CurrentWidget;
	uw->UpdatePlayersReady();

}
