#pragma once

#include "CoreMinimal.h"
#include "TouchInputSystem/Common/Data/EnumsStruct/FTouchInputInfo.h"
#include "UTouchSystemDelegates.generated.h"


UCLASS()
class TOUCHINPUTSYSTEM_API UTouchSystemDelegates : public UObject
{
	GENERATED_BODY()
	
private:
	static UTouchSystemDelegates* Singleton;

protected:
	virtual void BeginDestroy() override;
	
public:

	DECLARE_DELEGATE(FOnNoParams);
	DECLARE_DELEGATE_OneParam(FOnBool, bool);
	DECLARE_DELEGATE_OneParam(FOnString, FString);
	DECLARE_DELEGATE_OneParam(FOnByte, uint8);

	DECLARE_MULTICAST_DELEGATE(FOnNoParamsMulti);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnBoolMulti, bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnFloatMulti, float);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnByteMulti, uint8);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStringMulti, FString);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTransformMulti, FTransform);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorMulti, AActor*);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoParamsDynMulti);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolDynMulti, bool, bValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatDynMulti, float, Value);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnByteDynMulti, uint8, Value);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTouchInputDynMulti, FTouchInputInfo, TouchInput);

	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnTouchInputMulti, FTouchInputInfo);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnVector2DInputMulti, FVector2D);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnByteAndTouchInputMulti, uint8, FTouchInputInfo);
	
	static UTouchSystemDelegates& Get();
	
	FOnTouchInputMulti MasterInputReceived;
	FOnTouchInputDynMulti MasterInputReceivedGlobal;
	FOnVector2DInputMulti TouchControlRotation;
};
