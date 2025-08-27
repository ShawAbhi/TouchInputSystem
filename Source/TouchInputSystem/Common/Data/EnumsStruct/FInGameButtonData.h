#pragma once

#include "CoreMinimal.h"
#include "ETouchMode.h"
#include "GameplayTagContainer.h"
#include "FInGameButtonData.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FInGameButtonData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem")
	bool bIsToggleButton = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem")
	bool bPassthroughTouch = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem")
	bool bRequireTouchMode = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem",
		meta  = (EditCondition = bRequireTouchMode, EditConditionHides))
	TArray<EEnum_TouchMode> TouchModeToUse { 
		EEnum_TouchMode::Pressed, 
		EEnum_TouchMode::Released, 
		EEnum_TouchMode::Moved 
	};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem")
	UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem")
	bool bTickTouchEvent = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem",
		meta  = (EditCondition = bTickTouchEvent, EditConditionHides))
	EEnum_TouchMode TouchModeToTick = EEnum_TouchMode::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem",
		meta  = (EditCondition = bTickTouchEvent, EditConditionHides))
	bool bSeparateActionToTick = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TouchSystem",
		meta = (EditCondition = bSeparateActionToTick, EditConditionHides))
	UInputAction* InputActionToTick = nullptr;

};
