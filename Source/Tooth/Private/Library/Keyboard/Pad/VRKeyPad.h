// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "Tooth.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetInteractionComponent.h"
#include "VRKeyPad.generated.h"

UENUM(BlueprintType)
enum class EKeyEventName : uint8 {
	ON_KEY		 = 1	UMETA(DisplayName = "Key"),
	ON_BACKSPACE = 2	UMETA(DisplayName = "Backspace"),
	ON_CAPSLOOK	 = 3	UMETA(DisplayName = "CapsLook"),
	ON_SPECIFIC	 = 4	UMETA(DisplayName = "Specific"),
	ON_ENTER	 = 5	UMETA(DisplayName = "Enter"),
	ON_ALPHA_BAT = 6	UMETA(DisplayName = "AlphaBat"),
};

/**
 * 
 */
UCLASS()
class UVRKeyPad : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, DisplayName = "InitComponent")
	void InitComponent(UVRKeyPad* KeypadInstance);
	void InitComponent_Implementation(UVRKeyPad* KeypadInstance);

	UFUNCTION(BlueprintCallable, DisplayName = "KeyClick")
	void OnKeyClicked(EKeyEventName EventName, FText Text);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	class AVRKeyboard* VRKeyboard;
};
