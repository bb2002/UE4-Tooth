// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ToothSettings.generated.h"

/**
 * 
 */
UCLASS()
class UToothSettings : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
		int32 GameLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
		FString PlayerUUID;

	UToothSettings();
};
