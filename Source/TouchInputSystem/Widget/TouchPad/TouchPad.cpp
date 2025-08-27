#include "TouchPad.h"

void UTouchPad::BroadcastControlRotation(const FVector2D ControlRotation)
{
	UTouchSystemDelegates::Get().TouchControlRotation.Broadcast(ControlRotation);
}
