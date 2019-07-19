// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "Tooth.h"
#include "GameFramework/Actor.h"
#include "Public/TimerManager.h"
#include "Library/WorldGen/ToothBlock.h"
#include "ToothCreater.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMapSizeChanged, int32, SizeX, int32, SizeY);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCeilDropped);

UENUM(BlueprintType)
enum class EGameLevel : uint8 {
	LEVEL_EASY		= 1	UMETA(DisplayName = "EASY"),
	LEVEL_NORMAL	= 2 UMETA(DisplayName = "NORMAL"),
	LEVEL_HARD		= 3	UMETA(DisplayName = "HARD"),
	LEVEL_EXPERT	= 4	UMETA(DisplayName = "EXPERT")
};

UCLASS()
class AToothCreater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToothCreater();

	UPROPERTY(BlueprintAssignable)
	FOnMapSizeChanged OnMapSizeChangeListener;

	UPROPERTY(BlueprintAssignable)
	FOnCeilDropped OnCeilAllDroppedListener;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Generate Tooth Map (Data : Inner data)
	UFUNCTION(BlueprintCallable, DisplayName="GenerateToothMap", Category = "ToothSettings|Switch")
	void GenerateToothMap();

	// Clear Tooth Map
	UFUNCTION(BlueprintCallable, DisplayName = "ClearToothMap", Category = "ToothSettings|Switch")
	void ClearToothMap();

	// Dropdown the ceil
	/**
	 * @Param DropSpeed		Drop speed (-1 = Auto)
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "DropTheCeil")
	void DropTheCeil(float DropSpeed = -1);

	void DropTheCeilCallback();

	// 맵 생성기를 초기화 합니다.
	UFUNCTION(BlueprintCallable, DisplayName = "InitCreater")
	void InitCreater();

	// 맵 생성후, 중앙 위치를 가져옵니다.
	UFUNCTION(BlueprintPure, DisplayName = "GetCenterVector")
	FVector GetCenterVector();

	// 필요한 인스턴스를 생성합니다.
	FVector CreateNeedActors();

	// 맵의 크기를 (갯수 단위) 불러옵니다.
	UFUNCTION(BlueprintPure, DisplayName = "GetMapSize")
	FVector GetMapSize();

	// 블럭의 크기를 불러옵니다.
	UFUNCTION(BlueprintPure, DisplayName = "GetToothBlockSize")
	FVector GetToothBlockSize();

	// 울퉁불퉁 맵을 생성합니다.
	UFUNCTION()
	int32 RollingMap(TArray<FVector>& OutMap);

	// 스테이지 레벨을 올립니다.
	UFUNCTION(BlueprintCallable, DisplayName = "StageLevelUp")
	void StageLevelUp(int32 UpLevel = 1);

	// Actor Location CleanUp
	UFUNCTION(BlueprintCallable, DisplayName = "LocationCleanUp")
	void LocationCleanUp();
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ToothSettings|Mesh", Meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AToothBlock>> ToothMeshClass;

	// Stage Index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToothSettings|Difficult", Meta = (AllowPrivateAccess = true))
	int32 StageIndex;

	// Game Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToothSettings|Difficult", Meta = (AllowPrivateAccess = true))
	EGameLevel GameLevel;

	// Array size X 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ToothSettings|Difficult|Map", Meta = (AllowPrivateAccess = true))
	int32 ToothSizeX;

	// Array size Y
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ToothSettings|Difficult|Map", Meta = (AllowPrivateAccess = true))
	int32 ToothSizeY;

	// Array size Z
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ToothSettings|Difficult|Map", Meta = (AllowPrivateAccess = true))
	int32 ToothSizeZ;

	// Actor Reference of All actors.
	UPROPERTY()
	TArray<AToothBlock*> ToothBlockRefArray;

	// Top Reference of All actors.
	UPROPERTY()
	TArray<AToothBlock*> TopToothRef;

	// Bottom Reference of All actors.
	UPROPERTY()
	TArray<AToothBlock*> BottomToothRef;

	FTimerHandle ToothTimerHandler;
	float ToothCloseTime;

	UPROPERTY()
	FVector CenterVector;

	// 답
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ToothSettings|Map", Meta = (AllowPrivateAccess = true))
	TArray<FVector2D> KotaeArray;

};

int operator+(int lVal, EGameLevel rVal);

int operator+(EGameLevel lVal, int rVal);

int operator*(int lVal, EGameLevel rVal);

int operator*(EGameLevel lVal, int rVal);
