#pragma once
#include "UObject.h"
class AActor;
// UActorComponent 모든 부품들의 추상클래스다.
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

