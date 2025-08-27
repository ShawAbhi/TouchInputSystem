// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTouchButton.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"


void UBaseTouchButton::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (((ButtonData.bIsToggleButton && bIsActive) || bWasPressed) && ButtonData.bTickTouchEvent)
	{
		Payload.bIsToggle = (ButtonData.bIsToggleButton && bIsActive) ? false : ButtonData.bIsToggleButton;
		Payload.TouchEventType = ButtonData.TouchModeToTick;

		if (ButtonData.bSeparateActionToTick && IsValid(ButtonData.InputActionToTick))
		{
			BroadcastInputAction(ButtonData.InputActionToTick, ButtonData.TouchModeToTick);
		}
		else if (IsValid(ButtonData.InputAction))
		{
			BroadcastInputAction(ButtonData.InputAction, ButtonData.TouchModeToTick);
		}
	}
	if (bIsTouchHeld && IsValid(InputSubsystem))
	{
		if (!IsValid(DownTrigger))
		{
			DownTrigger = NewObject<UInputTriggerPressed>();
		}
		const TArray<UInputModifier*> Modifiers;
		InputSubsystem->InjectInputForAction(InputActionToTick, FInputActionValue(true), Modifiers, {DownTrigger});
	}
}

void UBaseTouchButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ListenForAbility();

	UTouchSystemDelegates::Get().MasterInputReceived.AddUObject(this, &UBaseTouchButton::HandleMasterTouchMessage);
}

void UBaseTouchButton::NativeDestruct()
{
	if (UTouchSystemDelegates::Get().MasterInputReceived.IsBoundToObject(this) && InputDelegateHandle.IsValid())
	{
		UTouchSystemDelegates::Get().MasterInputReceived.Remove(InputDelegateHandle);
	}
	Super::NativeDestruct();
}

FReply UBaseTouchButton::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchStarted(InGeometry, InGestureEvent);

	bWasPressed = true;
	TouchGeometry = InGeometry;
	ListenToTouchIndexMessages(InGestureEvent.GetPointerIndex());

	if (!ButtonData.bPassthroughTouch)
	{
		EventOnPressed(Payload.FingerLocation);
		OnPressed.Broadcast(FVector(InGestureEvent.GetScreenSpacePosition(), 0.0f));
	}

	return ButtonData.bPassthroughTouch ? FReply::Unhandled() : FReply::Handled();
}

FReply UBaseTouchButton::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchEnded(InGeometry, InGestureEvent);

	if (InGestureEvent.GetPointerIndex() != CurrentPointerIndex)
	{
		return FReply::Unhandled();
	}
	if (ButtonData.bPassthroughTouch)
	{
		return FReply::Unhandled();
	}
	EventOnReleased(Payload.FingerLocation);
	OnReleased.Broadcast(FVector(InGestureEvent.GetScreenSpacePosition(), 0.0f));

	return FReply::Handled();
}

FReply UBaseTouchButton::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchMoved(InGeometry, InGestureEvent);

	if (InGestureEvent.GetPointerIndex() != CurrentPointerIndex)
	{
		return FReply::Unhandled();
	}
	if (ButtonData.bPassthroughTouch)
	{
		return FReply::Unhandled();
	}
	EventOnMoved(Payload.FingerLocation);
	OnMoved.Broadcast(FVector(InGestureEvent.GetScreenSpacePosition(), 0.0f));

	return FReply::Handled();
}

void UBaseTouchButton::ListenToTouchIndexMessages(const int& PointerIndex)
{
	if (CurrentPointerIndex == PointerIndex)
	{
		return;
	}

	if (UTouchSystemDelegates::Get().MasterInputReceived.IsBoundToObject(this) && InputDelegateHandle.IsValid())
	{
		UTouchSystemDelegates::Get().MasterInputReceived.Remove(InputDelegateHandle);
	}

	CurrentPointerIndex = PointerIndex;
	InputDelegateHandle = UTouchSystemDelegates::Get().MasterInputReceived.AddUObject(this, &UBaseTouchButton::HandleTouchIndexMessages);
}

void UBaseTouchButton::HandleTouchIndexMessages(const FTouchInputInfo TouchInfo)
{
	if (!bWasPressed || CurrentPointerIndex != TouchInfo.TouchIndex)
	{
		return;
	}
	Payload = TouchInfo;

	OnEventReceived.Broadcast(Payload.FingerLocation, Payload.TouchEventType);
	EventOnEventReceived(Payload.FingerLocation, Payload.TouchEventType);

	if (IsValid(ButtonData.InputAction))
	{
		Payload.bIsToggle = ButtonData.bIsToggleButton;
		OnInputReceivedDelegate.Broadcast(Payload);
		BroadcastInputAction(ButtonData.InputAction,Payload.TouchEventType);
	}
	switch (Payload.TouchEventType)
	{
	case EEnum_TouchMode::Pressed:
		{
			EventOnPressed(Payload.FingerLocation);
			OnPressed.Broadcast(Payload.FingerLocation);
			break;
		}

	case EEnum_TouchMode::Released:
		{
			EventOnReleased(Payload.FingerLocation);
			OnReleased.Broadcast(Payload.FingerLocation);
			bWasPressed = false;
			break;
		}

	case EEnum_TouchMode::Moved:
		{
			EventOnMoved(Payload.FingerLocation);
			OnMoved.Broadcast(Payload.FingerLocation);
			break;
		}

	default:
		{
			// Handle unexpected cases (optional)
			break;
		}
	}
}

void UBaseTouchButton::SetIsActive_Implementation(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
}

void UBaseTouchButton::ListenForAbility()
{
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (ButtonData.InputAction)
		{
			EnhancedInput->BindAction(ButtonData.InputAction, ETriggerEvent::Triggered, this, &UBaseTouchButton::SetButtonActive);
			EnhancedInput->BindAction(ButtonData.InputAction, ETriggerEvent::Canceled, this, &UBaseTouchButton::SetButtonInactive);
		}
	}
}

void UBaseTouchButton::BroadcastInputAction(const UInputAction* InputActionToCall, EEnum_TouchMode Touch, FVector2D TouchLocation)
{
	if (bInjectDefaultActionValue)
	{
		InjectValueToInput(DefaultActionValue);
	}
}

void UBaseTouchButton::InjectValueToInputEvent_Implementation(UInputAction* InputActionToCall, FInputActionValue ActionValue)
{
	if (!InputActionToCall) return;
	
	const APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!IsValid(InputSubsystem))
	{
		InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	}

	if (IsValid(InputSubsystem))
	{
		if (UEnhancedPlayerInput* PlayerInput = InputSubsystem->GetPlayerInput())
		{
			PlayerInput->InjectInputForAction(InputActionToCall, ActionValue);
		}
	}

}

void UBaseTouchButton::InjectInputToTouchEvent(UInputAction* InputActionToCall, EEnum_TouchMode TouchMode)
{
	if (!InputActionToCall) return;
	const APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PC) return;

	if (!IsValid(InputSubsystem))
	{
		InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	}
	
	if (IsValid(InputSubsystem))
	{
		const TArray<UInputModifier*> Modifiers;
		TArray<UInputTrigger*> Triggers;

		switch (TouchMode)
		{
		case EEnum_TouchMode::Pressed:
			{
				UInputTriggerPressed* PressedTrigger = NewObject<UInputTriggerPressed>();
				Triggers.Add(PressedTrigger);
				bIsTouchHeld = true;
				InputActionToTick = InputActionToCall;
				break;
			}
		case EEnum_TouchMode::Released:
			{
				UInputTriggerReleased* ReleasedTrigger = NewObject<UInputTriggerReleased>();
				bIsTouchHeld = false;
				Triggers.Add(ReleasedTrigger);
				break;
			}
		case EEnum_TouchMode::Moved:
			{
				UInputTriggerHold* MoveAsHold = NewObject<UInputTriggerHold>();
				// Optional: Configure hold trigger (e.g. HoldTimeThreshold)
				MoveAsHold->HoldTimeThreshold = 0.01f;
				Triggers.Add(MoveAsHold);
				break;
			}
		case EEnum_TouchMode::Tap:
			{
				UInputTriggerTap* TapTrigger = NewObject<UInputTriggerTap>();
				Triggers.Add(TapTrigger);
				break;
			}
		case EEnum_TouchMode::Hold:
			{
				UInputTriggerHold* HoldTrigger = NewObject<UInputTriggerHold>();
				HoldTrigger->HoldTimeThreshold = 0.01f; // Customize as needed
				Triggers.Add(HoldTrigger);
				break;
			}
		case EEnum_TouchMode::HoldReleased:
			{
				UInputTriggerHoldAndRelease* ReleaseTrigger = NewObject<UInputTriggerHoldAndRelease>();

				Triggers.Add(ReleaseTrigger);
				bIsTouchHeld = false;

				break;
			}
		case EEnum_TouchMode::None:
			{
				break;
			}
		default:
			// No triggers added
				break;
		}
		
		// Final call for modes that are not Tap/HoldReleased (those already called return)
		InputSubsystem->InjectInputForAction(InputActionToCall, FInputActionValue(true), Modifiers, Triggers);
	}
}


void UBaseTouchButton::InjectValueToInput_Implementation(FInputActionValue ActionValue)
{
	if (!ButtonData.InputAction) return;

	const APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PC) return;

	if (!IsValid(InputSubsystem))
	{
		InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	}

	if (!ButtonData.bRequireTouchMode)
	{
		if (IsValid(InputSubsystem))
		{
			if (UEnhancedPlayerInput* PlayerInput = InputSubsystem->GetPlayerInput())
			{
				PlayerInput->InjectInputForAction(ButtonData.InputAction, ActionValue);
			}
		}
		return;
	}
	
	if (!ButtonData.TouchModeToUse.Contains(Payload.TouchEventType))
	{
		return;
	}

	if (IsValid(InputSubsystem))
	{
		const TArray<UInputModifier*> Modifiers;
		TArray<UInputTrigger*> Triggers;

		switch (Payload.TouchEventType)
		{
		case EEnum_TouchMode::Pressed:
			{
				UInputTriggerPressed* PressedTrigger = NewObject<UInputTriggerPressed>();
				Triggers.Add(PressedTrigger);
				bIsTouchHeld = ButtonData.TouchModeToUse.Contains(EEnum_TouchMode::Released);
				if (bIsTouchHeld)
				{
					InputActionToTick = ButtonData.InputAction;
				}
				break;
			}
		case EEnum_TouchMode::Released:
			{
				UInputTriggerReleased* ReleasedTrigger = NewObject<UInputTriggerReleased>();
				bIsTouchHeld = false;
				Triggers.Add(ReleasedTrigger);
				break;
			}
		case EEnum_TouchMode::Moved:
			{
				UInputTriggerHold* MoveAsHold = NewObject<UInputTriggerHold>();
				// Optional: Configure hold trigger (e.g. HoldTimeThreshold)
				MoveAsHold->HoldTimeThreshold = 0.01f;
				Triggers.Add(MoveAsHold);
				break;
			}
		case EEnum_TouchMode::Tap:
			{
				UInputTriggerTap* TapTrigger = NewObject<UInputTriggerTap>();
				Triggers.Add(TapTrigger);
				break;
			}
		case EEnum_TouchMode::Hold:
			{
				UInputTriggerHold* HoldTrigger = NewObject<UInputTriggerHold>();
				HoldTrigger->HoldTimeThreshold = 0.01f; // Customize as needed
				Triggers.Add(HoldTrigger);
				break;
			}
		case EEnum_TouchMode::HoldReleased:
			{
				UInputTriggerHoldAndRelease* ReleaseTrigger = NewObject<UInputTriggerHoldAndRelease>();

				Triggers.Add(ReleaseTrigger);
				bIsTouchHeld = false;

				break;
			}
		case EEnum_TouchMode::None:
			{
				break;
			}
		default:
			// No triggers added
			break;
		}

		// Final call for modes that are not Tap/HoldReleased (those already called return)
		InputSubsystem->InjectInputForAction(ButtonData.InputAction, ActionValue, Modifiers, Triggers);
	}
}


void UBaseTouchButton::SetButtonActive()
{
	SetIsActive(true);
}

void UBaseTouchButton::SetButtonInactive()
{
	SetIsActive(false);
}

void UBaseTouchButton::EventOnPressed_Implementation(const FVector& FingerLocation)
{
}

void UBaseTouchButton::EventOnReleased_Implementation(const FVector& FingerLocation)
{
}

void UBaseTouchButton::EventOnMoved_Implementation(const FVector& FingerLocation)
{
}

void UBaseTouchButton::EventOnEventReceived_Implementation(const FVector& FingerLocation, EEnum_TouchMode TouchMode)
{
}