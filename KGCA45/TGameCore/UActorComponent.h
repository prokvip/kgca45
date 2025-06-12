#pragma once
#include "UObject.h"
class AActor;
// UActorComponent ��� ��ǰ���� �߻�Ŭ������.
class UActorComponent : public UObject
{
protected:
	AActor* m_pOwner = nullptr;
public:
	AActor* GetOwner();
	void	SetOwner(AActor* pOwner);
public:
	virtual void   TickComponent();
public:
	UActorComponent(std::wstring name);
	UActorComponent();
	virtual ~UActorComponent();
};

