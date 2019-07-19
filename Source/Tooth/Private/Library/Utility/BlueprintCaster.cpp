// Copyright (c) 2015-2019 Saint software All rights reserved.

#include "BlueprintCaster.h"

EGameLevel UBlueprintCaster::IntToGameLevel(int32 GameLevel) {
	switch (GameLevel) {
	case 1:
		return EGameLevel::LEVEL_EASY;
	case 2:
		return EGameLevel::LEVEL_NORMAL;
	case 3:
		return EGameLevel::LEVEL_HARD;
	case 4:
		return EGameLevel::LEVEL_EXPERT;
	default:
		return EGameLevel::LEVEL_EASY;
	}
}

int32 UBlueprintCaster::GameLevelToInt(EGameLevel GameLevel)
{
	switch (GameLevel) {
	case EGameLevel::LEVEL_EASY:
		return 1;
	case EGameLevel::LEVEL_NORMAL:
		return 2;
	case EGameLevel::LEVEL_HARD:
		return 3;
	case EGameLevel::LEVEL_EXPERT:
		return 4;
	default:
		return 1;
	}
}

FVector2D UBlueprintCaster::DegreeToOrient(float degree, EButtonOrient Orient)
{
	if (degree < 0) {
		degree = 360 + degree;
	}

	switch(Orient) {
	case EButtonOrient::BTN_FORWARD: break;
	case EButtonOrient::BTN_BACKWARD: degree += 180; break;
	case EButtonOrient::BTN_RIGHT: degree += 90; break;
	case EButtonOrient::BTN_LEFT: degree += 270; break;
	}

	if (degree >= 360) degree -= 360;

	UE_LOG(ToothLog, Warning, TEXT("DEGREE : %d"), degree);

	if (degree >= 337.5 && degree < 360 || degree >= 0 && degree < 22.5) {
		// Move Forward.
		return FVector2D(1, 0);
	}
	else if (degree >= 22.5 && degree < 67.5) {
		// Move Forward+Right
		return FVector2D(1, 1);
	}
	else if (degree >= 67.5 && degree < 112.5) {
		// Move Right
		return FVector2D(0, 1);
	}
	else if (degree >= 112.5 && degree < 157.5) {
		// Move Right Backward
		return FVector2D(-1, 1);
	}
	else if (degree >= 157.5 && degree < 202.5) {
		// Move Backward
		return FVector2D(-1, 0);
	}
	else if (degree >= 202.5 && degree < 247.5) {
		// Move Left + Backward
		return FVector2D(-1, -1);
	}
	else if (degree >= 247.5 && degree < 292.5) {
		// Move Left
		return FVector2D(0, -1);
	}
	else if (degree >= 292.5 && degree < 337.5) {
		// Move Left + Forward
		return FVector2D(1, -1);
	}
	else {
		return FVector2D(0, 0);
	}
}
