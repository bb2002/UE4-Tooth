// Copyright (c) 2015-2019 Saint software All rights reserved.

#include "ToothSettings.h"
#include "Public/Misc/Guid.h"

UToothSettings::UToothSettings() {
	PlayerName = FString(TEXT("Player"));
	GameLevel = 1;
	PlayerUUID = FGuid::NewGuid().ToString();
}