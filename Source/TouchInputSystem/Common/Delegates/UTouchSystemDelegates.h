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

	DECLARE_DELEGATE(FDelegateZeroParams);
	DECLARE_DELEGATE_OneParam(FDelegateOneParamBool, bool);
	DECLARE_DELEGATE_OneParam(FDelegateOneParamFString, FString);
	DECLARE_DELEGATE_OneParam(FDelegateOneParamUint8, uint8);

	DECLARE_MULTICAST_DELEGATE(FMulticastDelegateZeroParams);
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamBool, bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamFloat, float);
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamUint8, uint8);
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamFString, FString);
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamFTransform, FTransform);
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamAActor, AActor*);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicMulticastDelegateZeroParams);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMulticastDelegateOneParamBool, bool, bValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMulticastDelegateOneParamFloat, float, Value);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMulticastDelegateOneParamUint8, uint8, Value);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMulticastDelegateOneParamInputStruct, FTouchInputInfo, TouchInput);
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamInputStruct, FTouchInputInfo);
	DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParamFVector2D, FVector2D);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastDelegateTwoParamUint8InputStruct, uint8, FTouchInputInfo);
	
	static UTouchSystemDelegates& Get();
	
	FMulticastDelegateOneParamInputStruct MasterInputReceived;
	FMulticastDelegateOneParamFVector2D TouchControlRotation;
};
