#pragma once
#include "UActorComponent.h"
class USoundComponent :  public UActorComponent
{
public:
	virtual void    TickComponent() override;
public:
	USoundComponent(std::wstring name);
	USoundComponent();
	~USoundComponent();
};

