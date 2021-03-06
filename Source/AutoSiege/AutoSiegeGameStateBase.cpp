#include "AutoSiegeGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "AutoSiegeUserWidget.h"

void AAutoSiegeGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAutoSiegeGameStateBase, RoundTimer);
	DOREPLIFETIME(AAutoSiegeGameStateBase, Heroes);
	DOREPLIFETIME(AAutoSiegeGameStateBase, CurrentStage);
}
