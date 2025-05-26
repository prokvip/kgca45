#pragma once
#include "TStd.h"
#include "TRect.h"

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
	UObject(std::wstring name);
	UObject();
	virtual ~UObject();
};

