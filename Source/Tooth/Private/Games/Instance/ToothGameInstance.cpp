// Fill out your copyright notice in the Description page of Project Settings.

#include "ToothGameInstance.h"

UToothGameInstance::UToothGameInstance() {
	NewScore = -1;
	NewStage = -1;
}

UToothSettings* UToothGameInstance::LoadGameSettings() {
	UToothSettings* SettingInstance = Cast<UToothSettings>(UGameplayStatics::LoadGameFromSlot(GAME_SETTINGS_SLOT, 0));
	
	if (SettingInstance == nullptr) {
		return Cast<UToothSettings>(UGameplayStatics::CreateSaveGameObject(UToothSettings::StaticClass()));
	}
	else {
		return SettingInstance;
	}
}

UToothRanking* UToothGameInstance::LoadGameRanking()
{
	UToothRanking* RankingInstance = Cast<UToothRanking>(UGameplayStatics::LoadGameFromSlot(GAME_RANKING_SLOT, 0));
	
	if (RankingInstance == nullptr) {
		return Cast<UToothRanking>(UGameplayStatics::CreateSaveGameObject(UToothRanking::StaticClass()));
	}
	else {
		return RankingInstance;
	}

	return RankingInstance;
}

void UToothGameInstance::SaveGameSettings(FString PlayerNickname, int32 Level)
{
	auto NewGameSettings = Cast<UToothSettings>(UGameplayStatics::CreateSaveGameObject(UToothSettings::StaticClass()));
	NewGameSettings->PlayerName = PlayerNickname;
	NewGameSettings->GameLevel = Level;

	UGameplayStatics::SaveGameToSlot(NewGameSettings, GAME_SETTINGS_SLOT, 0);
}

void UToothGameInstance::SaveGameRanking(int32 HighestLevel, int32 HighestScore)
{
	auto NewGameRanking = Cast<UToothRanking>(UGameplayStatics::CreateSaveGameObject(UToothRanking::StaticClass()));
	NewGameRanking->HighestLevel = HighestLevel;
	NewGameRanking->HighestScore = HighestScore;

	UGameplayStatics::SaveGameToSlot(NewGameRanking, GAME_RANKING_SLOT, 0);
}

const FString UToothGameInstance::GAME_SETTINGS_SLOT = TEXT("Settings");
const FString UToothGameInstance::GAME_RANKING_SLOT = TEXT("Ranking");
