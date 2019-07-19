// Copyright (c) 2015-2019 Saint software All rights reserved.

#include "ToothBlock.h"

// Sets default values
AToothBlock::AToothBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ToothMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToothMesh"));
	RootComponent = ToothMeshComponent;
}

// Called when the game starts or when spawned
void AToothBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToothBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AToothBlock::GetToothBlockSize()
{
	// Calc this block size.
	FTransform transform;
	return ToothMeshComponent->CalcBounds(transform).GetBox().GetSize();
}

