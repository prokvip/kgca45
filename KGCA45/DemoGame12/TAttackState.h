#pragma once
#include "TObjectState.h"
class TAttackState : public TObjectState
{
public:
	virtual void Process(APawn* pPlayer)  override;
	TAttackState(ANpc* pOwner);
	TAttackState() = default; 
};

