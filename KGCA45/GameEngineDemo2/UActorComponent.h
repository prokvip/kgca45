#pragma once
#include "UObject.h"
// UActorComponent 모든 부품들의 추상클래스다.
class UActorComponent : public UObject
{
private:
	std::wstring  m_szName;
	static int    m_iNumInstance;
public:
	virtual void   TickComponent() {};// = 0;
public:
	std::wstring GetName() const;
	void		 SetName(std::wstring name);
	static int	 GetNumInstance();
public:
	UActorComponent(std::wstring name);
	UActorComponent();
	virtual ~UActorComponent();
};

