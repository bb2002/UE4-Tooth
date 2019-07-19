// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ToothRanking.generated.h"

/**
 * 
 */
UCLASS()
class UToothRanking : public USaveGame
{
	GENERATED_BODY()

public:
	// 최고 레벨
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ranking")
		int32 HighestLevel;

	// 최고 스코어
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ranking")
		int32 HighestScore;

	UToothRanking();
	
};
