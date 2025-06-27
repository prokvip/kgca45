#pragma once
#include "ANpc.h"

class TNpcManager :   public UObject
{
public:
	TFsm<TNpcStateEvent>	m_Fsm; // 상태머신
	TNpcStateEvent& GetDefinition()
	{
		return m_Fsm.Definition;
	}
	TFsm<TNpcStateEvent>& GetFsm()
	{
		return m_Fsm;
	}
	TObjectState* m_pCurrentState = nullptr;
	std::shared_ptr<TObjectState> m_pStop = nullptr;
	std::shared_ptr<TObjectState> m_pMove = nullptr;
	std::shared_ptr<TObjectState> m_pAttack = nullptr;
	std::vector<std::shared_ptr<TObjectState>> m_StateList;

	static TNpcManager& Get()
	{
		static TNpcManager mgr;
		return mgr;
	}
	static TFsm<TNpcStateEvent>& FSM()
	{		
		return TNpcManager::Get().m_Fsm;
	}
public:
	virtual void Init();
	virtual void Tick();
	virtual void Render();
public:
	TNpcManager();
	virtual ~TNpcManager();
};

