#pragma once
#include "UActorComponent.h"
class USoundComponent :  public UActorComponent
{
public:
	USoundComponent(std::wstring name);
	USoundComponent();
	~USoundComponent();
};

