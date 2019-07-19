// Copyright (c) 2015-2019 Saint software All rights reserved.

#include "VRKeyPad.h"
#include "Library/Keyboard/VRKeyboard.h"

void UVRKeyPad::InitComponent_Implementation(UVRKeyPad* KeypadInstance) {

}

void UVRKeyPad::OnKeyClicked(EKeyEventName EventName, FText Text) {
	UWidgetInteractionComponent* InteractionCompo = VRKeyboard->GetWidgetInteractionComponent();


	if (InteractionCompo == nullptr || VRKeyboard == nullptr) {
		UE_LOG(ToothLog, Error, TEXT("InteractionCompo OR VRKeyboard is null."));
	}
	else {
		switch (EventName) {
		case EKeyEventName::ON_KEY:
			InteractionCompo->SendKeyChar(Text.ToString(), false);
			break;

		case EKeyEventName::ON_BACKSPACE:
			InteractionCompo->PressAndReleaseKey(FKey(EKeys::BackSpace));
			break;

		case EKeyEventName::ON_ENTER:
			VRKeyboard->EnterClick();
			break;

		case EKeyEventName::ON_CAPSLOOK:
			if (VRKeyboard->GetKeyPadType() == EVRKeyPadType::PAD_CAPSLOOK_OFF) {
				VRKeyboard->SwitchKeypad(EVRKeyPadType::PAD_CAPSLOOK_ON);
			}
			else {
				VRKeyboard->SwitchKeypad(EVRKeyPadType::PAD_CAPSLOOK_OFF);
			}
			break;

		case EKeyEventName::ON_SPECIFIC:
			VRKeyboard->SwitchKeypad(EVRKeyPadType::PAD_SPECIFIC_ON);
			break;

		case EKeyEventName::ON_ALPHA_BAT:
			VRKeyboard->SwitchKeypad(EVRKeyPadType::PAD_CAPSLOOK_OFF);
			break;
		}
	}
}