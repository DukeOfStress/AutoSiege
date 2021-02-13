#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "Board.generated.h"

UCLASS()
class AUTOSIEGE_API ABoard : public AActor
{

	GENERATED_BODY()
	
public:	
	ABoard();

	//UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* StaticMeshComponent;

	//UPROPERTY(VisibleAnywhere)
	//UCameraComponent* CameraComponent;

	//UPROPERTY(VisibleAnywhere)
	//USkyLightComponent* SkyLightComponent;

	//UPROPERTY(VisibleAnywhere)
	//UDirectionalLightComponent* DirectionalLightComponent;

};
