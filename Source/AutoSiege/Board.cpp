#include "Board.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = false;


	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	//StaticMeshComponent->SetRelativeScale3D(FVector(41.25f, 23.75f, 1.0f));
	//
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BoardMesh(TEXT("StaticMesh'/Game/Meshes/SquarePlane_Mesh.SquarePlane_Mesh'"));
	//if (BoardMesh.Object != NULL){
	//	StaticMeshComponent->SetStaticMesh( (UStaticMesh*)BoardMesh.Object );
	//}

	//static ConstructorHelpers::FObjectFinder<UMaterial> BoardMaterial(TEXT("Material'/Game/Materials/Board_Mat.Board_Mat'"));
	//if( BoardMaterial.Object != NULL ){
	//	StaticMeshComponent->SetMaterial( 0, (UMaterial*)BoardMaterial.Object );
	//}


	//CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	//CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 1990.0f));
	//CameraComponent->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));
	//CameraComponent->SetActive(true);


	//DirectionalLightComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Directional Light Component"));
	//DirectionalLightComponent->SetRelativeLocation(FVector(170.0f, -1310.0f, 355.0f));
	//DirectionalLightComponent->SetRelativeRotation(FRotator(52.0f, -78.0f, -88.0f));
	//DirectionalLightComponent->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
	//DirectionalLightComponent->SetMobility(EComponentMobility::Stationary);
	//DirectionalLightComponent->SetIntensity(1.435f);
	//DirectionalLightComponent->bUsedAsAtmosphereSunLight = true;

}
