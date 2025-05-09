#pragma once
#include <iostream>
#include <string>
// UActorComponent ��� ��ǰ���� �߻�Ŭ������.
class UActorComponent
{
private:
	std::wstring  m_szName;
	static int    m_iNumInstance;
public:
	
public:
	std::wstring GetName() const;
	void		 SetName(std::wstring name);
	static int	 GetNumInstance();
public:
	UActorComponent(std::wstring name);
	UActorComponent();
	~UActorComponent();
};

