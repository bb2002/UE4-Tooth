// Copyright (c) 2015-2019 Saint software All rights reserved.

#include "VRKeyboard.h"
#include "Public/Blueprint/UserWidget.h"

// Sets default values
AVRKeyboard::AVRKeyboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	KeypadComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyboardComponent"));

	KeypadComponent->SetupAttachment(RootSceneComponent);
	KeypadComponent->SetWidgetClass(CapsLookOffPad);

	RootComponent = RootSceneComponent;
}

// Called when the game starts or when spawned
void AVRKeyboard::BeginPlay()
{
	Super::BeginPlay();

	// Create Keyboard Pad
	CapsLookOnPadIns = CreateWidget<UVRKeyPad>(GetWorld(), CapsLookOnPad, TEXT("CapsLookOnPad"));
	CapsLookOffPadIns = CreateWidget<UVRKeyPad>(GetWorld(), CapsLookOffPad, TEXT("CapsLookOffPad"));
	SpecificPadIns = CreateWidget<UVRKeyPad>(GetWorld(), SpecificPad, TEXT("SpecificPad"));

	// Init Keyboard Pad
	CapsLookOnPadIns->VRKeyboard = this;
	CapsLookOffPadIns->VRKeyboard = this;
	SpecificPadIns->VRKeyboard = this;

	KeypadComponent->SetDrawSize(FVector2D(1055, 480));
	KeypadComponent->SetWidget(CapsLookOffPadIns);

	CapsLookOnPadIns->InitComponent(CapsLookOnPadIns);
	CapsLookOffPadIns->InitComponent(CapsLookOffPadIns);
	SpecificPadIns->InitComponent(SpecificPadIns);
}

void AVRKeyboard::SwitchKeypad(EVRKeyPadType KeyPadType)
{
	switch (KeyPadType) {
	case EVRKeyPadType::PAD_CAPSLOOK_ON:
		if (CapsLookOnPadIns == nullptr)	KeypadComponent->SetWidget(CapsLookOnPadIns);
		break;
	case EVRKeyPadType::PAD_CAPSLOOK_OFF:
		if (CapsLookOffPadIns == nullptr)	KeypadComponent->SetWidget(CapsLookOffPadIns);
		break;
	case EVRKeyPadType::PAD_SPECIFIC_ON:
		if (SpecificPadIns == nullptr)		KeypadComponent->SetWidget(SpecificPadIns);
		break;
	}
}

void AVRKeyboard::SetWidgetInteractionComponent(UWidgetInteractionComponent * WidgetInteraction)
{
	this->InteractionComponent = WidgetInteraction;
}

UWidgetInteractionComponent * AVRKeyboard::GetWidgetInteractionComponent()
{
	return InteractionComponent;
}

EVRKeyPadType AVRKeyboard::GetKeyPadType()
{
	return NowKeyPadType;
}

void AVRKeyboard::EnterClick()
{
	OnEnterClickListener.Broadcast();
}

