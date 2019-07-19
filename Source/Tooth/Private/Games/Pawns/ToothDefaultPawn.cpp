// Fill out your copyright notice in the Description page of Project Settings.

#include "ToothDefaultPawn.h"
#include "Components/InputComponent.h"

// Sets default values
AToothDefaultPawn::AToothDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Components.
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	VRCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRootScene"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	WidgetInteractor = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractor"));
	MotionControllerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MotionControllerMesh"));
	HttpRequesterComponent = CreateDefaultSubobject<UGameHttpRequester>(TEXT("HttpRequestComponent"));

	// Init Components.
	RootComponent = RootScene;
	VRCameraRoot->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(VRCameraRoot);
	MotionController->SetupAttachment(VRCameraRoot);
	WidgetInteractor->SetupAttachment(MotionController);
	MotionControllerMesh->SetupAttachment(MotionController);

	

	MotionController->MotionSource = TEXT("Right");
}

// Called when the game starts or when spawned
void AToothDefaultPawn::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AToothDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AToothDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	FInputActionBinding TriggerPressBind("TriggerClick", IE_Pressed);
	TriggerPressBind.ActionDelegate.GetDelegateForManualSet().BindLambda([this] {
		WidgetInteractor->PressPointerKey(FKey(EKeys::LeftMouseButton));
	});
	PlayerInputComponent->AddActionBinding(TriggerPressBind);

	FInputActionBinding TriggerReleaseBind("TriggerClick", IE_Released);
	TriggerReleaseBind.ActionDelegate.GetDelegateForManualSet().BindLambda([this] {
		WidgetInteractor->ReleasePointerKey(FKey(EKeys::LeftMouseButton));
	});
	PlayerInputComponent->AddActionBinding(TriggerReleaseBind);

}

