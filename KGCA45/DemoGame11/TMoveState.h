#pragma once
#include "TObjectState.h"
class TMoveState :  public TObjectState
{
public:
	virtual void Process(APawn* pPlayer) override;
	TMoveState(ANpc* pOwner);
};

