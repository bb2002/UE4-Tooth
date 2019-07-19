// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ServerRankingObject.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FServerRankingObject
{
	GENERATED_USTRUCT_BODY()

public:
	FServerRankingObject() {

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	FString PlayerNickname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerUUID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HighestStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HighestScore;
};
