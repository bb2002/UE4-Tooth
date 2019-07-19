// Fill out your copyright notice in the Description page of Project Settings.

#include "ToothDefaultGameMode.h"
#include "Games/Instance/ToothGameInstance.h"

UToothSettings* AToothDefaultGameMode::LoadGameSettings() {
	UToothGameInstance* Instance = Cast<UToothGameInstance>(GetGameInstance());
	return Instance->LoadGameSettings();
}

UToothRanking* AToothDefaultGameMode::LoadGameRanking()
{
	UToothGameInstance* Instance = Cast<UToothGameInstance>(GetGameInstance());
	return Instance->LoadGameRanking();
}

void AToothDefaultGameMode::SaveGameSettings(FString PlayerNickname, int32 Level)
{
	UToothGameInstance* Instance = Cast<UToothGameInstance>(GetGameInstance());
	Instance->SaveGameSettings(PlayerNickname, Level);
}

void AToothDefaultGameMode::SaveGameRanking(int32 HighestLevel, int32 HighestScore)
{
	UToothGameInstance* Instance = Cast<UToothGameInstance>(GetGameInstance());
	Instance->SaveGameRanking(HighestLevel, HighestScore);
}

const FString AToothDefaultGameMode::GAME_SETTINGS_SLOT = TEXT("Settings");
const FString AToothDefaultGameMode::GAME_RANKING_SLOT = TEXT("Ranking");
