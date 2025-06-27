#include "TNpcManager.h"
#include "TAttackState.h"
#include "TStopState.h"
#include "TMoveState.h"
void TNpcManager::Tick()
{

}
void TNpcManager::Render()
{

}
void TNpcManager::Init()
{
	/*m_pStop = std::make_shared<TStopState>(this);
	m_pMove = std::make_shared<TMoveState>(this);
	m_pAttack = std::make_shared<TAttackState>(this);
	m_StateList.emplace_back(m_pStop);
	m_StateList.emplace_back(m_pMove);
	m_StateList.emplace_back(m_pAttack);
	m_pCurrentState = m_pStop.get();*/

	// 상태 구조 초기화
	// 현재상태			  이벤트			상태전환(전이)
	// STATE_STOP		 EVENT_TIMEOUT				STATE_MOVE
	// STATE_STOP		 EVENT_FINDTARGET			STATE_ATTACK
	// STATE_MOVE		 EVENT_TIMEOUT				STATE_STOP
	// STATE_MOVE		 EVENT_FINDTARGET			STATE_ATTACK
	// STATE_ATTACK		 EVENT_LOSTTARGET			STATE_MOVE
	// STATE_ATTACK		 EVENT_TIMEOUT				STATE_STOP
	m_Fsm.AddStateTransition(m_Fsm.Definition.STATE_STOP,
		m_Fsm.Definition.EVENT_TIMEOUT,
		m_Fsm.Definition.STATE_MOVE);
	m_Fsm.AddStateTransition(m_Fsm.Definition.STATE_STOP,
		m_Fsm.Definition.EVENT_FINDTARGET,
		m_Fsm.Definition.STATE_ATTACK);
	m_Fsm.AddStateTransition(m_Fsm.Definition.STATE_MOVE,
		m_Fsm.Definition.EVENT_TIMEOUT,
		m_Fsm.Definition.STATE_STOP);
	m_Fsm.AddStateTransition(m_Fsm.Definition.STATE_MOVE,
		m_Fsm.Definition.EVENT_FINDTARGET,
		m_Fsm.Definition.STATE_ATTACK);
	m_Fsm.AddStateTransition(m_Fsm.Definition.STATE_ATTACK,
		m_Fsm.Definition.EVENT_LOSTTARGET,
		m_Fsm.Definition.STATE_MOVE);
	m_Fsm.AddStateTransition(m_Fsm.Definition.STATE_ATTACK,
		m_Fsm.Definition.EVENT_TIMEOUT,
		m_Fsm.Definition.STATE_STOP);
}
TNpcManager::TNpcManager()
{
}
TNpcManager::~TNpcManager()
{	
}