#pragma once
#include "UObject.h"
// UActorComponent ��� ��ǰ���� �߻�Ŭ������.
class UActorComponent : public UObject
{
public:
	virtual void   TickComponent();
public:
	UActorComponent(std::wstring name);
	UActorComponent();
	virtual ~UActorComponent();
};

