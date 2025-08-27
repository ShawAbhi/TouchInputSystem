#include "UTouchSystemDelegates.h"

UTouchSystemDelegates* UTouchSystemDelegates::Singleton = nullptr;

UTouchSystemDelegates& UTouchSystemDelegates::Get()
{
	if (!Singleton)
	{
		Singleton = NewObject<UTouchSystemDelegates>();
		Singleton->AddToRoot(); // Prevents GC
	}
	return *Singleton;
}

void UTouchSystemDelegates::BeginDestroy()
{
	Super::BeginDestroy();

	if (this == Singleton)
	{
		RemoveFromRoot();
		Singleton = nullptr;
	}
}