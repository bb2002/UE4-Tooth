// Copyright (c) 2015-2019 Saint software All rights reserved.

#include "MovementGrid.h"

// Sets default values
AMovementGrid::AMovementGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootScene;
}

// Called when the game starts or when spawned
void AMovementGrid::BeginPlay()
{
	Super::BeginPlay();
	
	// Search ToothGenerater.
	for (TActorIterator<AToothCreater> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		CurrentToothGen = *ActorItr;
	}

	if (CurrentToothGen == nullptr) {
		UE_LOG(ToothLog, Error, TEXT("ToothGenerater is not found!!!!"));
		return;
	}

	// Sync Location.
	SetActorLocation(CurrentToothGen->GetActorLocation());

	// Bind Event
	CurrentToothGen->OnMapSizeChangeListener.AddDynamic(this, &AMovementGrid::OnMapSizeChange);
}

// Called every frame
void AMovementGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovementGrid::Invalidate(int32 MapX, int32 MapY) {
	FVector DrawSize = CurrentToothGen->GetMapSize();

	if (MapX != -1 && MapY != -1) {
		DrawSize.X = MapX;
		DrawSize.Y = MapY;
	}

	FVector ToothBlockSize = CurrentToothGen->GetToothBlockSize();
	FVector CurrentVector = GetActorLocation();

	for (int x = 0; x < DrawSize.X; ++x) {
		for (int y = 0; y < DrawSize.Y; ++y) {
			float xPos = CurrentVector.X + x * ToothBlockSize.X;
			float yPos = CurrentVector.Y + y * ToothBlockSize.Y;
			MapGrid.Add(FVector2D(x, y), FVector(xPos, yPos, 0.0f));
		}
	}
}

void AMovementGrid::OnMapSizeChange(int32 MapX, int32 MapY)
{
	Invalidate(MapX, MapY);
}

FVector AMovementGrid::XYPositionToLocation(int32 MapX, int32 MapY)
{
	FVector* TmpLocation = MapGrid.Find(FVector2D(MapX, MapY));

	if (TmpLocation == nullptr) {
		return FVector::ZeroVector;
	}
	else {
		return *TmpLocation;
	}

}

