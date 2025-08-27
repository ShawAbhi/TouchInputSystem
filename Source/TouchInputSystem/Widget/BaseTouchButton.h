// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputTriggers.h"
#include "TouchInputSystem/Common/Data/EnumsStruct/FInGameButtonData.h"
#include "TouchInputSystem/Common/Data/EnumsStruct/FTouchInputInfo.h"
#include "TouchInputSystem/Common/Delegates/UTouchSystemDelegates.h"
#include "Blueprint/UserWidget.h"
#include "BaseTouchButton.generated.h"


class UInputModifier;
class UInputTriggerPressed;
class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionValue;
DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamFVector, FVector);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastDelegateTwoParamsFVectorEnumTouchMode, FVector,EEnum_TouchMode);


struct FTouchInputInfo;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class TOUCHINPUTSYSTEM_API UBaseTouchButton : public UUserWidget
{
	GENERATED_BODY()
	
private:
	bool bIsActive{false};
	bool bIsTouchHeld{false};
	UPROPERTY()
	UInputTriggerPressed* DownTrigger;
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
	FDelegateHandle InputDelegateHandle;
	FTouchInputInfo Payload;
	UPROPERTY()
	UInputAction* InputActionToTick;
	UFUNCTION()
	void SetButtonActive();
	UFUNCTION()
	void SetButtonInactive();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "BaseInGameButton")
	int CurrentPointerIndex{-1};
	UPROPERTY(BlueprintReadWrite, Category = "BaseInGameButton")
	bool bWasPressed{false};
	UPROPERTY(BlueprintReadWrite, Category = "BaseInGameButton")
	FGeometry TouchGeometry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseInGameButton")
	bool bInjectDefaultActionValue{true};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseInGameButton",
	meta  = (EditCondition = bInjectDefaultActionValue, EditConditionHides))
	FInputActionValue DefaultActionValue{FInputActionValue(true)}; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseInGameButton")
	FInGameButtonData ButtonData;

	UPROPERTY(BlueprintAssignable, Category="Collision")
	UTouchSystemDelegates::FDynamicMulticastDelegateOneParamInputStruct OnInputReceivedDelegate;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
	
	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;

	void ListenToTouchIndexMessages(const int& PointerIndex);
	UFUNCTION()
	void HandleTouchIndexMessages(const FTouchInputInfo TouchInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BaseInGameButton")
	void SetIsActive(bool bNewIsActive);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BaseInGameButton")
	bool GetIsActive() const { return bIsActive; }

	void ListenForAbility();
	void BroadcastInputAction(const UInputAction* InputActionToCall, EEnum_TouchMode Touch, FVector2D TouchLocation = FVector2D::ZeroVector);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BaseInGameButton")
	void InjectValueToInput(FInputActionValue ActionValue);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BaseInGameButton")
	void InjectValueToInputEvent(UInputAction* InputActionToCall, FInputActionValue ActionValue);
	UFUNCTION(BlueprintCallable, Category = "BaseInGameButton")
	void InjectInputToTouchEvent(UInputAction* InputActionToCall, EEnum_TouchMode TouchMode);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FTouchInputInfo GetPayload() const { return Payload; }
	
public:

	FMulticastDelegateOneParamFVector OnPressed;
	FMulticastDelegateOneParamFVector OnReleased;
	FMulticastDelegateOneParamFVector OnMoved;
	FMulticastDelegateTwoParamsFVectorEnumTouchMode OnEventReceived;

	UFUNCTION(BlueprintNativeEvent, Category = "BaseInGameButton")
	void EventOnPressed(const FVector& FingerLocation);
	UFUNCTION(BlueprintNativeEvent, Category = "BaseInGameButton")
	void EventOnReleased(const FVector& FingerLocation);
	UFUNCTION(BlueprintNativeEvent, Category = "BaseInGameButton")
	void EventOnMoved(const FVector& FingerLocation);
	UFUNCTION(BlueprintNativeEvent, Category = "BaseInGameButton")
	void EventOnEventReceived(const FVector& FingerLocation, EEnum_TouchMode TouchMode);
	
};
