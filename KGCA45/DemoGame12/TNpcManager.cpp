#include "TNpcManager.h"
#include "TAttackState.h"
#include "TStopState.h"
#include "TMoveState.h"
void TNpcManager::Frame()
{

}
void TNpcManager::Render()
{

}
void TNpcManager::Init()
{
	m_Pattern.resize(3);
	// 상태 구조 초기화
	// 현재상태			  이벤트			상태전환(전이)
	// STATE_STOP		 EVENT_TIMEOUT				STATE_MOVE
	// STATE_MOVE		 EVENT_TIMEOUT				STATE_STOP
	m_Pattern[0].m_pStop = std::make_shared<TStopState>();
	m_Pattern[0].m_pMove = std::make_shared<TMoveState>();
	m_Pattern[0].m_StateList.emplace_back(m_Pattern[0].m_pStop);
	m_Pattern[0].m_StateList.emplace_back(m_Pattern[0].m_pMove);
	m_Pattern[0].m_Fsm.AddStateTransition(STATE_STOP, EVENT_TIMEOUT, STATE_MOVE);
	m_Pattern[0].m_Fsm.AddStateTransition(STATE_MOVE, EVENT_TIMEOUT, STATE_STOP);
	// 현재상태			  이벤트			상태전환(전이)
	// STATE_STOP		 EVENT_FINDTARGET			STATE_ATTACK
	// STATE_ATTACK		 EVENT_LOSTTARGET			STATE_MOVE
	// STATE_ATTACK		 EVENT_TIMEOUT				STATE_STOP
	m_Pattern[1].m_pStop = std::make_shared<TStopState>();
	m_Pattern[1].m_pAttack = std::make_shared<TAttackState>();
	m_Pattern[1].m_StateList.emplace_back(m_Pattern[0].m_pStop);
	m_Pattern[1].m_StateList.emplace_back(m_Pattern[0].m_pAttack);
	m_Pattern[1].m_Fsm.AddStateTransition(STATE_STOP, EVENT_TIMEOUT, STATE_MOVE);
	m_Pattern[1].m_Fsm.AddStateTransition(STATE_ATTACK, EVENT_LOSTTARGET, STATE_MOVE);
	m_Pattern[1].m_Fsm.AddStateTransition(STATE_ATTACK, EVENT_TIMEOUT, STATE_STOP);

	// 현재상태			  이벤트			상태전환(전이)
	// STATE_STOP		 EVENT_TIMEOUT				STATE_MOVE
	// STATE_STOP		 EVENT_FINDTARGET			STATE_ATTACK
	// STATE_MOVE		 EVENT_TIMEOUT				STATE_STOP
	// STATE_MOVE		 EVENT_FINDTARGET			STATE_ATTACK
	// STATE_ATTACK		 EVENT_LOSTTARGET			STATE_MOVE
	// STATE_ATTACK		 EVENT_TIMEOUT				STATE_STOP
	m_Pattern[2].m_pStop = std::make_shared<TStopState>();
	m_Pattern[2].m_pMove = std::make_shared<TMoveState>();
	m_Pattern[2].m_pAttack = std::make_shared<TAttackState>();
	m_Pattern[2].m_StateList.emplace_back(m_Pattern[0].m_pStop);
	m_Pattern[2].m_StateList.emplace_back(m_Pattern[0].m_pMove);
	m_Pattern[2].m_StateList.emplace_back(m_Pattern[0].m_pAttack);
	m_Pattern[2].m_Fsm.AddStateTransition(STATE_STOP, EVENT_TIMEOUT, STATE_MOVE);
	m_Pattern[2].m_Fsm.AddStateTransition(STATE_STOP, EVENT_FINDTARGET, STATE_ATTACK);
	m_Pattern[2].m_Fsm.AddStateTransition(STATE_MOVE, EVENT_TIMEOUT, STATE_STOP);
	m_Pattern[2].m_Fsm.AddStateTransition(STATE_MOVE, EVENT_FINDTARGET, STATE_ATTACK);
	m_Pattern[2].m_Fsm.AddStateTransition(STATE_ATTACK, EVENT_LOSTTARGET, STATE_MOVE);
	m_Pattern[2].m_Fsm.AddStateTransition(STATE_ATTACK, EVENT_TIMEOUT, STATE_STOP);
}
TNpcManager::TNpcManager()
{
}
TNpcManager::~TNpcManager()
{	
}