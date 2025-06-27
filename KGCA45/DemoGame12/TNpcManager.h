#pragma once
#include "ANpc.h"

class TFsmPattern
{
public:
	TFsm			m_Fsm; // 상태머신	
	TObjectState* m_pCurrentState = nullptr;
	std::shared_ptr<TObjectState> m_pStop = nullptr;
	std::shared_ptr<TObjectState> m_pMove = nullptr;
	std::shared_ptr<TObjectState> m_pAttack = nullptr;
	std::vector<std::shared_ptr<TObjectState>> m_StateList;
};
class TNpcManager :   public UObject
{
	std::vector<TFsmPattern>     m_Pattern;
public:	
	TFsmPattern& GetPattern(int type=0)
	{
		return m_Pattern[type];
	}
	TFsm& GetFsm(int type = 0)
	{
		return m_Pattern[0].m_Fsm;
	}
public:
	virtual void Init();
	virtual void Tick();
	virtual void Render();
public:
	TNpcManager();
	virtual ~TNpcManager();
};

