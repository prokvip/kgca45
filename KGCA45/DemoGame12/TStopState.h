#pragma once
#include "TObjectState.h"
class TStopState :   public TObjectState
{
public:
	virtual void Process(APawn* pPlayer) override;
	TStopState(ANpc* pOwner);
	TStopState() = default;
};

