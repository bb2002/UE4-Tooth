// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Games/Saves/ToothSettings.h"
#include "Games/Saves/ToothRanking.h"
#include "ToothDefaultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AToothDefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	const static FString GAME_SETTINGS_SLOT;
	const static FString GAME_RANKING_SLOT;

	UFUNCTION(BlueprintCallable, DisplayName="LoadGameSettings", Category="ToothSave")
	UToothSettings* LoadGameSettings();

	UFUNCTION(BlueprintCallable, DisplayName = "LoadGameRanking", Category = "ToothSave")
	UToothRanking* LoadGameRanking();

	UFUNCTION(BlueprintCallable, DisplayName = "SaveGameSettings", Category = "ToothSave")
	void SaveGameSettings(FString PlayerNickname, int32 Level);

	UFUNCTION(BlueprintCallable, DisplayName = "SaveGameRanking", Category = "ToothSave")
	void SaveGameRanking(int32 HighestLevel, int32 HighestScore);
};
