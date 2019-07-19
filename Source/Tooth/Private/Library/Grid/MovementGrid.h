// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "Tooth.h"
#include "GameFramework/Actor.h"
#include "Library/WorldGen/ToothCreater.h"
#include "EngineUtils.h"
#include "MovementGrid.generated.h"

UCLASS()
class AMovementGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovementGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, DisplayName = "Invalidate")
	void Invalidate(int32 MapX = -1, int32 MapY = -1);

	UFUNCTION()
	void OnMapSizeChange(int32 MapX, int32 MapY);

	UFUNCTION(BlueprintCallable, DisplayName = "XYPositionToLocation")
	FVector XYPositionToLocation(int32 MapX, int32 MapY);

private:
	UPROPERTY()
	AToothCreater* CurrentToothGen;

	UPROPERTY()
	TMap<FVector2D, FVector> MapGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	USceneComponent* RootScene;
};
