#pragma once
#include "TStd.h"
class TSprite
{
public:
	std::wstring			m_szName;
	float					m_fStep = 1.0f;
	UINT					m_iCurrentIndex = 0;
	float					gTimer = 0.0f;
	UINT				    m_iSecond = 0;
	TVector2				m_pInitPos;
	TVector2				m_pInitSize;
};

