#pragma once
#include "TRect.h"
#include <string>
#include <list>
#include <vector>
#include <memory> // smart point


class UObject
{	
	
private:
	std::wstring  m_szName;
	static int    m_iNumInstance;
public:
	virtual std::wstring GetName() const;
	virtual void		 SetName(std::wstring name);
	static int	 GetNumInstance();
public:
	// 대입연산자
	void operator=(const UObject& comp);
	// 복사 생성자
	UObject(const UObject& comp);
	UObject(std::wstring name);
	UObject();
	virtual ~UObject();
};

