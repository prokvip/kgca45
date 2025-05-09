#pragma once
#include "UActorComponent.h"
class UTimerComponent : public UActorComponent
{
public:
	UTimerComponent(std::wstring name);
	UTimerComponent();
	~UTimerComponent();
};

