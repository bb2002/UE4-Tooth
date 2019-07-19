// Copyright (c) 2015-2019 Saint software All rights reserved.

#include "ToothCreater.h"
#include "Classes/Engine/World.h"

// Sets default values
AToothCreater::AToothCreater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AToothCreater::BeginPlay()
{
	Super::BeginPlay();
	InitCreater();
}

void AToothCreater::GenerateToothMap()
{
	FVector CurrentVector = GetActorLocation();									// 맵 생성기 위치
	FVector TargetVector;														// 블럭의 요구 위치
	int32 BlockRefIndex = 0;													// 선택된 블럭 레퍼런스 인덱스
	int32 RollingCount = FMath::RandRange(1, GameLevel * StageIndex / 2 + 1);	// Z 축 깊이
	KotaeArray.Empty();

	if (ToothMeshClass.Num() == 0) {
		// 어떤 클래스도 선택되지 않았습니다.
		UE_LOG(LogTemp, Error, TEXT("ToothMeshClass is not inited."));
		return;
	}

	// Re Calc MapSize
	if (StageIndex % 8 == 0) {
		// 8 의 배수에서 X, Y 축을 1 씩 증가 합니다.
		ToothSizeX++;
		ToothSizeY++;
	}

	// Create Need Actors.
	FVector NewToothBlockSize = CreateNeedActors();
	TArray<FVector> RolledMap; RollingMap(RolledMap);
	bool isHanaCreated = false;		// 구멍이 만들어졌는가.
	TopToothRef.Empty(); BottomToothRef.Empty();

	for (int x = 0; x < ToothSizeX; ++x) {
		TargetVector.X = CurrentVector.X + (x * NewToothBlockSize.X);

		for (int y = 0; y < ToothSizeY; ++y) {
			TargetVector.Y = CurrentVector.Y + (y * NewToothBlockSize.Y);

			int32 ZIndexTop = ToothSizeZ / 2, ZIndexBottom = ToothSizeZ / 2;

			for (int m = 0; m < RolledMap.Num(); ++m) {
				FVector Map = RolledMap[m];

				if (Map.X == x && Map.Y == y) {
					ZIndexBottom += Map.Z;
					ZIndexTop += -Map.Z;

					// 답 생성
					if (FMath::RandBool()) {
						if (ZIndexBottom > ZIndexTop) ZIndexBottom--; else ZIndexTop--;
						isHanaCreated = true;

						// Add Result
						KotaeArray.Add(FVector2D(x, y));

					}
					break;
				}
			}

			if (x == ToothSizeX - 1 && y == ToothSizeY - 1 && !isHanaCreated) {
				ZIndexBottom--;
				KotaeArray.Add(FVector2D(x, y));
			}

			for (int32 bottom = 0; bottom < ZIndexBottom; ++bottom) {
				auto ToothBlock = ToothBlockRefArray[BlockRefIndex++];

				TargetVector.Z = CurrentVector.Z + (bottom * NewToothBlockSize.Z);
				ToothBlock->SetActorLocation(TargetVector);
				BottomToothRef.Add(ToothBlock);
			}

			for (int32 top = 0; top < ZIndexTop; ++top) {
				auto ToothBlock = ToothBlockRefArray[BlockRefIndex++];

				TargetVector.Z = CurrentVector.Z + top * NewToothBlockSize.Z + 1000 + (ToothSizeZ * NewToothBlockSize.Z - ZIndexTop * NewToothBlockSize.Z);
				ToothBlock->SetActorLocation(TargetVector);
				TopToothRef.Add(ToothBlock);
			}
		}
	}

	// Define center vector
	this->CenterVector = CurrentVector + FVector(NewToothBlockSize.X * ToothSizeX / 2, NewToothBlockSize.Y * ToothSizeY / 2, 0);
}

void AToothCreater::ClearToothMap()
{
	for (auto ToothBlock : ToothBlockRefArray) {
		// Destroy All Actors.
		ToothBlock->Destroy();
	}

	ToothBlockRefArray.Empty();
}

float DroppedSize = 0.0f;
const float DroppedSpeed = 20.0f;
FTimerHandle CeilDropTimer;
void AToothCreater::DropTheCeil(float DropSpeed)
{
	DroppedSize = 0.0f;
	FTimerManager& TimerManager = GetWorldTimerManager();

	TimerManager.SetTimer(CeilDropTimer, this, &AToothCreater::DropTheCeilCallback, 0.02f, true);
}

void AToothCreater::DropTheCeilCallback() {
	DroppedSize += DroppedSpeed;

	if (DroppedSize >= 1000) {
		// All Dropped.
		OnCeilAllDroppedListener.Broadcast();

		FTimerManager& TimerManager = GetWorldTimerManager();
		TimerManager.ClearTimer(CeilDropTimer);	// Clear timer.
		return;
	}
	else {
		// Drop down.
		for (auto Block : TopToothRef) {
			Block->AddActorLocalOffset(FVector(0, 0, -DroppedSpeed));
		}
	}
}

void AToothCreater::InitCreater()
{
	// Set Default Level
	this->ToothSizeX = this->ToothSizeY = GameLevel + 3;

	switch (GameLevel)
	{
	case EGameLevel::LEVEL_EASY: case EGameLevel::LEVEL_NORMAL:
		this->ToothSizeZ = 4; break;
	case EGameLevel::LEVEL_HARD: case EGameLevel::LEVEL_EXPERT:
		this->ToothSizeZ = 6; break;
	}
}

FVector AToothCreater::GetCenterVector()
{
	return CenterVector;
}

FVector AToothCreater::CreateNeedActors()
{
	UWorld* CurrentWorld = GetWorld();
	int32 NeedActors = ToothSizeX * ToothSizeY * ToothSizeZ - ToothBlockRefArray.Num();

	if (NeedActors >= 0) {
		// Create Actors.
		for (int i = 0; i < NeedActors; ++i) {
			int idx = FMath::RandRange(0, ToothMeshClass.Num() - 1);

			AToothBlock* NewToothBlock = CurrentWorld->SpawnActor<AToothBlock>(ToothMeshClass[idx]);
			ToothBlockRefArray.Add(NewToothBlock);
		}
	}
	else {
		// Delete Actors.
		ToothBlockRefArray.Pop()->Destroy();
	}

	// Broadcast Delegate
	OnMapSizeChangeListener.Broadcast(ToothSizeX, ToothSizeY);

	return ToothBlockRefArray[0]->GetToothBlockSize();
}

FVector AToothCreater::GetMapSize()
{
	return FVector(ToothSizeX, ToothSizeY, ToothSizeZ);
}

FVector AToothCreater::GetToothBlockSize()
{
	if (ToothBlockRefArray.Num() == 0) {
		return FVector::ZeroVector;
	}
	else {
		return ToothBlockRefArray[0]->GetToothBlockSize();
	}
}

int32 AToothCreater::RollingMap(TArray<FVector>& OutMap)
{
	int32 RollingCount = FMath::RandRange(StageIndex, StageIndex * GameLevel);
	int HanaCount = FMath::RandRange(1, 3);

	for (int i = 0; i < RollingCount; ++i) {
		int32 z = FMath::RandRange(-(ToothSizeZ / 2 - 1), ToothSizeZ / 2 - 1);
		if (z == 0) z++;

		OutMap.Add(FVector(FMath::RandRange(0, ToothSizeX - 1), FMath::RandRange(0, ToothSizeY - 1), z));
	}

	return RollingCount;
}

void AToothCreater::StageLevelUp(int32 UpLevel)
{
	StageIndex += UpLevel;
}

void AToothCreater::LocationCleanUp()
{
	for (auto Item : ToothBlockRefArray) {
		Item->SetActorLocation(FVector::ZeroVector);
	}
}

int operator+(int lVal, EGameLevel rVal) {
	switch (rVal) {
	case EGameLevel::LEVEL_EASY: return lVal + 1;
	case EGameLevel::LEVEL_NORMAL: return lVal + 2;
	case EGameLevel::LEVEL_HARD: return lVal + 3;
	case EGameLevel::LEVEL_EXPERT: return lVal + 4;
	}

	return 0;
}

int operator+(EGameLevel lVal, int rVal) {
	return rVal + lVal;
}

int operator*(int lVal, EGameLevel rVal) {
	switch (rVal) {
	case EGameLevel::LEVEL_EASY: return lVal * 1;
	case EGameLevel::LEVEL_NORMAL: return lVal * 2;
	case EGameLevel::LEVEL_HARD: return lVal * 3;
	case EGameLevel::LEVEL_EXPERT: return lVal * 4;
	}

	return 0;
}

int operator*(EGameLevel lVal, int rVal) {
	return rVal + lVal;
}
