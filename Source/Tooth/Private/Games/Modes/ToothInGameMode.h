// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Games/Modes/ToothDefaultGameMode.h"
#include "ToothInGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameReady);

/**
 * 
 */
UCLASS()
class AToothInGameMode : public AToothDefaultGameMode
{
	GENERATED_BODY()
	
public:
	/**
	 * 캐릭터를 월드 제너레이터의 0,0 위치로 이동 시킵니다.
	 * ! Be should InitGenerater()
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "MoveStartPosition")
	void MoveStartPosition();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ToothGame|System", Meta = (AllowPrivateAccess = true))
	float ToothWaitTime = 0.0f;

};
