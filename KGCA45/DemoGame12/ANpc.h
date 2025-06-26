#pragma once
#include "ANpcCharacter.h"
#include "TFsm.h"
#include "TObjectState.h"

class TNpcManager;

enum  ENpcState
{
	STATE_STOP = 0,
	STATE_MOVE,
	STATE_ATTACK,		
	STATE_COUNTER,
};
enum  ENpcEvent
{
	EVENT_STOP = 0,
	EVENT_TIMEOUT,
	EVENT_MOVE,
	EVENT_FINDTARGET,
	EVENT_LOSTTARGET,
	EVENT_COUNT,
};	

class ANpc :  public ANpcCharacter
{
public:
	int			  m_iPatternType = 0;
	TNpcManager*  m_pMgr = nullptr;
	TObjectState* m_pCurrentState = nullptr;
public:
	virtual void	Init() override;
	virtual void	Tick() override;
	virtual void	Movement();
public:
	ANpc(std::wstring name);
	ANpc();
	~ANpc();
};
