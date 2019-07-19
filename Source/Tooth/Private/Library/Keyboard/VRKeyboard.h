// Copyright (c) 2015-2019 Saint software All rights reserved.

#pragma once

#include "Tooth.h"
#include "GameFramework/Actor.h"
#include "Library/Keyboard/Pad/VRKeyPad.h"
#include "Components/WidgetComponent.h"
#include "VRKeyboard.generated.h"

UENUM(BlueprintType)
enum class EVRKeyPadType : uint8 {
	PAD_CAPSLOOK_ON = 1		UMETA(DisplayName = "CapsLook_On"),
	PAD_CAPSLOOK_OFF = 2	UMETA(DisplayName = "CapsLook_Off"),
	PAD_SPECIFIC_ON = 3		UMETA(DisplayName = "Specific_On")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterClicked);

UCLASS()
class AVRKeyboard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRKeyboard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, DisplayName = "SwitchKeypad")
	void SwitchKeypad(EVRKeyPadType KeyPadType);

	UFUNCTION(BlueprintCallable, DisplayName = "SetWidgetInteractionComponent")
	void SetWidgetInteractionComponent(UWidgetInteractionComponent* WidgetInteraction);

	UFUNCTION(BlueprintPure, DisplayName = "GetWidgetInteractionComponent")
	UWidgetInteractionComponent* GetWidgetInteractionComponent();

	UFUNCTION(BlueprintPure, DisplayName="GetKeypadType")
	EVRKeyPadType GetKeyPadType();

	UFUNCTION(BlueprintCallable, DisplayName = "EnterClick")
	void EnterClick();

public:
	FOnEnterClicked OnEnterClickListener;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "VRKeyboard|Pad", Meta = (AllowPrivateAccess = true))
	TSubclassOf<UVRKeyPad> CapsLookOnPad;

	UPROPERTY()
	UVRKeyPad* CapsLookOnPadIns;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "VRKeyboard|Pad", Meta = (AllowPrivateAccess = true))
	TSubclassOf<UVRKeyPad> CapsLookOffPad;

	UPROPERTY()
	UVRKeyPad* CapsLookOffPadIns;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "VRKeyboard|Pad", Meta = (AllowPrivateAccess = true))
	TSubclassOf<UVRKeyPad> SpecificPad;

	UPROPERTY()
	UVRKeyPad* SpecificPadIns;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRKeyboard|Widget", Meta = (AllowPrivateAccess = true))
	UWidgetComponent* KeypadComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRKeyboard|Interaction", Meta = (AllowPrivateAccess = true))
	UWidgetInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRKeyboard", Meta = (AllowPrivateAccess = true))
	USceneComponent* RootSceneComponent;

	EVRKeyPadType NowKeyPadType;
};
