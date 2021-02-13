#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"

#include "AutoSiegeUserWidget.generated.h"

UCLASS(Abstract)
class UAutoSiegeUserWidget : public UUserWidget
{

	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void UpdateRoundTimer();
	void UpdatePlayersReady();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* RoundTimer_Text = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PlayersReady_Text = nullptr;

};
