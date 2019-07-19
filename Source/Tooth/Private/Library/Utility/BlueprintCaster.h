// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Library/WorldGen/ToothCreater.h"
#include "BlueprintCaster.generated.h"

UENUM(BlueprintType)
enum class EButtonOrient : uint8 {
	BTN_FORWARD		= 1 UMETA(DisplayName = "Forward"),
	BTN_BACKWARD	= 2 UMETA(DisplayName = "Backward"),
	BTN_LEFT		= 3 UMETA(DisplayName = "Left"),
	BTN_RIGHT		= 4 UMETA(DisplayName = "Right")
};

/**
 * 
 */
UCLASS()
class UBlueprintCaster : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Utility|Caster", DisplayName="IntToGameLevel")
	static EGameLevel IntToGameLevel(int32 GameLevel);

	UFUNCTION(BlueprintPure, Category = "Utility|Caster", DisplayName = "GameLevelToInt")
	static int32 GameLevelToInt(EGameLevel GameLevel);

	UFUNCTION(BlueprintPure, Category = "Utility|Caster", DisplayName = "DegreeToOrient")
	static FVector2D DegreeToOrient(float degree, EButtonOrient Orient);
};
