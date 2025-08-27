// Fill out your copyright notice in the Description page of Project Settings.


#include "TouchInputFunctions.h"

#include "TouchInputSystem/Common/Delegates/UTouchSystemDelegates.h"

void UTouchInputFunctions::BroadcastTouchInputs(const FTouchInputInfo& TouchInputs)
{
	UTouchSystemDelegates::Get().MasterInputReceived.Broadcast(TouchInputs);
	UTouchSystemDelegates::Get().MasterInputReceivedGlobal.Broadcast(TouchInputs);
}
