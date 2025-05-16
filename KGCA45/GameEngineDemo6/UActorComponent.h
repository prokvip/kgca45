#pragma once
#include "UObject.h"
// UActorComponent 모든 부품들의 추상클래스다.
class UActorComponent : public UObject
{
public:
	virtual void   TickComponent();
public:
	UActorComponent(std::wstring name);
	UActorComponent();
	virtual ~UActorComponent();
};

