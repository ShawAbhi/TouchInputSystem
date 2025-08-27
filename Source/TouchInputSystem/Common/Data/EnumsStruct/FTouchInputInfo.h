#pragma once

#include "CoreMinimal.h"
#include "ETouchMode.h"
#include "FTouchInputInfo.generated.h"

USTRUCT(BlueprintType)
struct FTouchInputInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TouchSystem")
	FVector FingerLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TouchSystem")
	EEnum_TouchMode TouchEventType = EEnum_TouchMode::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TouchSystem")
	bool bIsToggle = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TouchSystem")
	TEnumAsByte<ETouchIndex::Type> TouchIndex = ETouchIndex::Type::Touch1;
};
