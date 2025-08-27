// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TouchInputSystem/Widget/BaseTouchButton.h"
#include "TouchJoystick.generated.h"

class UImage;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class TOUCHINPUTSYSTEM_API UTouchJoystick : public UBaseTouchButton
{
	GENERATED_BODY()

private:
	FVector2D InitialCenterPosition;
	FVector2D UpdateThumbPadAnchor;

	FVector FinalDirection;
	float FinalScale;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Joystick", meta = (BindWidget))
	UCanvasPanel* BasePanel;
	UPROPERTY(BlueprintReadOnly, Category = "Joystick", meta = (BindWidget))
	UImage* ThumbPadImage;
	UPROPERTY(BlueprintReadOnly, Category = "Joystick", meta = (BindWidget))
	UImage* BackgroundImage;
	UPROPERTY(BlueprintReadOnly, Category = "Joystick")
	FVector2D TouchOriginalScale;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	void UpdateJoystick(const FVector2D& Position);
	void UpdateOutput();
	void UpdateThumbPad(const FVector2D& Direction, float Scale);
	void RevertThumbPad(const float DeltaTime);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Joystick")
	FVector2D GetCenterPosition();

	virtual void EventOnPressed_Implementation(const FVector& FingerLocation) override;
	virtual void EventOnMoved_Implementation(const FVector& FingerLocation) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void JoystickOutput(const FVector& Direction, const float Scale);
};
