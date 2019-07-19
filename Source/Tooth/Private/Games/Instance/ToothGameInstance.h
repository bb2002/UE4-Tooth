// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Games/Saves/ToothSettings.h"
#include "Games/Saves/ToothRanking.h"
#include "ToothGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UToothGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UToothGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataSender|Game")
	int32 NewScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataSender|Game")
	int32 NewStage;



	const static FString GAME_SETTINGS_SLOT;
	const static FString GAME_RANKING_SLOT;

	UFUNCTION(BlueprintCallable, DisplayName = "LoadGameSettings", Category = "ToothSave")
		UToothSettings* LoadGameSettings();

	UFUNCTION(BlueprintCallable, DisplayName = "LoadGameRanking", Category = "ToothSave")
		UToothRanking* LoadGameRanking();

	UFUNCTION(BlueprintCallable, DisplayName = "SaveGameSettings", Category = "ToothSave")
		void SaveGameSettings(FString PlayerNickname, int32 Level);

	UFUNCTION(BlueprintCallable, DisplayName = "SaveGameRanking", Category = "ToothSave")
		void SaveGameRanking(int32 HighestLevel, int32 HighestScore);
	
};
