#pragma once
#include "UObject.h"
// UActorComponent ��� ��ǰ���� �߻�Ŭ������.
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

