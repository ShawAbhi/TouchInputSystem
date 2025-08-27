// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TouchInputFunctions.generated.h"

struct FTouchInputInfo;
/**
 * 
 */
UCLASS()
class TOUCHINPUTSYSTEM_API UTouchInputFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "TouchInput")
	static void BroadcastTouchInputs(const FTouchInputInfo& TouchInputs);
};
