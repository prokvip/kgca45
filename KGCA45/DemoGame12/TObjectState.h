#pragma once
#include "TStd.h"
class ANpc;
class APawn;
class TObjectState
{
public:
	ANpc* m_pOwner = nullptr;
	float m_Timer = 0.0f;
public:
	virtual void Process(APawn* pPlayer) = 0;
	TObjectState(ANpc* pOwner);
	TObjectState();
};

