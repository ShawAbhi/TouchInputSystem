// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchJoystick.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"


void UTouchJoystick::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTouchJoystick::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	RevertThumbPad(InDeltaTime);
	UpdateOutput();
}

void UTouchJoystick::UpdateOutput()
{
	FinalDirection = UKismetMathLibrary::GetDirectionUnitVector(
		FVector(0.5f), FVector(UpdateThumbPadAnchor.X, UpdateThumbPadAnchor.Y, 0.5f));
	FinalScale = UKismetMathLibrary::Distance2D(UpdateThumbPadAnchor, FVector2D(0.5f)) * 2.0f;

	JoystickOutput(FVector(FinalDirection.X, FinalDirection.Y, 0.5f), FinalScale);
}

void UTouchJoystick::RevertThumbPad(const float DeltaTime)
{
	if (UCanvasPanelSlot* ThumbPadSlot = Cast<UCanvasPanelSlot>(ThumbPadImage->Slot))
	{
		const FVector2D CurrentAnchors = ThumbPadSlot->GetAnchors().Minimum;
		if (bWasPressed || CurrentAnchors == FVector2D(0.5f))
		{
			return;
		}

		const FVector2D Anchors = UKismetMathLibrary::Vector2DInterpTo(CurrentAnchors,
		                                                               FVector2D(0.5f),
		                                                               DeltaTime, 10.0f);
		ThumbPadSlot->SetAnchors(FAnchors(Anchors.X, Anchors.Y));
	}
}


void UTouchJoystick::EventOnPressed_Implementation(const FVector& FingerLocation)
{
	UpdateJoystick(FVector2D(FingerLocation.X, FingerLocation.Y));
	Super::EventOnPressed_Implementation(FingerLocation);
}

void UTouchJoystick::EventOnMoved_Implementation(const FVector& FingerLocation)
{
	UpdateJoystick(FVector2D(FingerLocation.X, FingerLocation.Y));
	Super::EventOnMoved_Implementation(FingerLocation);
}

void UTouchJoystick::UpdateJoystick(const FVector2D& Position)
{
	if (!bWasPressed)
	{
		return;
	}
	FVector2D LocalPosition;
	USlateBlueprintLibrary::ScreenToWidgetLocal(this, TouchGeometry, Position, LocalPosition);

	const FVector2D PanelSize = BasePanel->GetCachedGeometry().GetLocalSize();
	const FVector2D Target2D = (LocalPosition - GetCenterPosition()) / PanelSize + FVector2D(0.5f);

	const FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(
		FVector(0.5f), FVector(Target2D.X, Target2D.Y, 0.5f));
	const float Scale = UKismetMathLibrary::Distance2D(Target2D, FVector2D(0.5f));

	UpdateThumbPad(FVector2D(Direction.X, Direction.Y), UKismetMathLibrary::FMin(Scale, 0.5f));

	TouchOriginalScale = FVector2D(Target2D.X - 0.5f, Target2D.Y - 0.5f);
}

void UTouchJoystick::UpdateThumbPad(const FVector2D& Direction, float Scale)
{
	if (UCanvasPanelSlot* ThumbPadSlot = Cast<UCanvasPanelSlot>(ThumbPadImage->Slot))
	{
		UpdateThumbPadAnchor = Direction * FVector2D(Scale) + FVector2D(0.5f);
		ThumbPadSlot->SetAnchors(FAnchors(UpdateThumbPadAnchor.X, UpdateThumbPadAnchor.Y));
	}
}

FVector2D UTouchJoystick::GetCenterPosition()
{
	FVector2D ThumbLocalPosition;
	USlateBlueprintLibrary::ScreenToWidgetLocal(this, ThumbPadImage->GetCachedGeometry(), FVector2D::ZeroVector,
	                                            ThumbLocalPosition);
	FVector2D BGLocalPosition;
	USlateBlueprintLibrary::ScreenToWidgetLocal(this, BackgroundImage->GetCachedGeometry(), FVector2D::ZeroVector,
	                                            BGLocalPosition);
	if (InitialCenterPosition == FVector2D::ZeroVector)
	{
		InitialCenterPosition = ThumbPadImage->GetCachedGeometry().GetLocalSize() * 0.5f - (ThumbLocalPosition -
			BGLocalPosition);
	}
	return InitialCenterPosition;
}

void UTouchJoystick::JoystickOutput_Implementation(const FVector& Direction, const float Scale)
{
	const FInputActionValue ActionValue = FVector2D(Direction.X * Scale, Direction.Y * -Scale);
	InjectValueToInput_Implementation(ActionValue);
}
