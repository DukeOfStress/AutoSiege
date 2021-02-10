#include "AutoSiegePlayerState.h"
#include "AutoSiegePlayerController.h"

AAutoSiegePlayerState::AAutoSiegePlayerState() 
{
    AvailableHeroes = {};
}

void AAutoSiegePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AAutoSiegePlayerState, PlayerIndex);
    DOREPLIFETIME(AAutoSiegePlayerState, AvailableHeroes);
    DOREPLIFETIME(AAutoSiegePlayerState, ChosenHero);
}

void AAutoSiegePlayerState::OnRep_AvailableHeroes()
{
    if (!HasAuthority() && AvailableHeroes.Num() == 3)
    {
        AAutoSiegePlayerController* pc = GetWorld()->GetFirstPlayerController<AAutoSiegePlayerController>();
        pc->InitHeroSelect();
            
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnRep_AvailableHeroes - %d - %s"), PlayerIndex , *(AvailableHeroes[i]).ToString()));
    }
}