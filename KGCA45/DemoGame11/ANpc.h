#pragma once
#include "ANpcCharacter.h"
#include "TFsm.h"
#include "TObjectState.h"

class TNpcManager;

struct TNpcStateEvent
{
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
	// 현재상태			  이벤트			상태전환(전이)
	// STATE_STOP		 EVENT_TIMEOUT				STATE_MOVE
	// STATE_STOP		 EVENT_FINDTARGET			STATE_ATTACK
	// STATE_MOVE		 EVENT_TIMEOUT				STATE_STOP
	// STATE_MOVE		 EVENT_FINDTARGET			STATE_ATTACK
	// STATE_ATTACK		 EVENT_LOSTTARGET			STATE_STOP
	// STATE_ATTACK		 EVENT_TIMEOUT				STATE_STOP
	// STATE_ATTACK		 EVENT_LOSTTARGET			STATE_MOVE
};
class ANpc :  public ANpcCharacter
{
public:
	TFsm<TNpcStateEvent>	m_Fsm; // 상태머신
	TNpcStateEvent& GetDefinition()
	{
		return m_Fsm.Definition;
	}
	TObjectState* m_pCurrentState = nullptr;
	std::shared_ptr<TObjectState> m_pStop = nullptr;
	std::shared_ptr<TObjectState> m_pMove = nullptr;
	std::shared_ptr<TObjectState> m_pAttack = nullptr;	
	std::vector<std::shared_ptr<TObjectState>> m_StateList;
public:
	virtual void	Init() override;
	virtual void	Tick() override;
	virtual void	Movement();
public:
	ANpc(std::wstring name);
	ANpc();
	~ANpc();
};

class ANpcFsm : public ANpcCharacter
{
public:
	TFsm<TNpcStateEvent>* m_pFsm; // 상태머신
	TNpcStateEvent& GetDefinition()
	{
		return m_pFsm->Definition;
	}
public:
	virtual void	Init();
};