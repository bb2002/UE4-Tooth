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
	 * ĳ���͸� ���� ���ʷ������� 0,0 ��ġ�� �̵� ��ŵ�ϴ�.
	 * ! Be should InitGenerater()
	*/
	UFUNCTION(BlueprintCallable, DisplayName = "MoveStartPosition")
	void MoveStartPosition();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ToothGame|System", Meta = (AllowPrivateAccess = true))
	float ToothWaitTime = 0.0f;

};
