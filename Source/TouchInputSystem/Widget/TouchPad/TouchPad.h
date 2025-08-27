

#pragma once

#include "CoreMinimal.h"
#include "TouchInputSystem/Widget/BaseTouchButton.h"
#include "TouchPad.generated.h"

/**
 * 
 */
UCLASS()
class TOUCHINPUTSYSTEM_API UTouchPad : public UBaseTouchButton
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "TouchPad")
	void BroadcastControlRotation(const FVector2D ControlRotation);
};
