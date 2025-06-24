#include "ANpc.h"
#include "TAttackState.h"
#include "TStopState.h"
#include "TMoveState.h"
#include "UWorld.h"
#include "TNpcManager.h"
void   ANpc::Init()
{
	m_pStop = std::make_shared<TStopState>(this);
	m_pMove = std::make_shared<TMoveState>(this);
	m_pAttack = std::make_shared<TAttackState>(this);
	m_StateList.emplace_back(m_pStop);
	m_StateList.emplace_back(m_pMove);
	m_StateList.emplace_back(m_pAttack);
	m_pCurrentState = m_pStop.get();

	// ���� ���� �ʱ�ȭ
	// �������			  �̺�Ʈ			������ȯ(����)
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
void	ANpc::Tick()
{
	m_pCurrentState->Process((APawn*)UWorld::m_pPlayer.get());
	ANpcCharacter::Tick();
}
void ANpc::Movement()
{
	TVector2 pos = GetPosition();
	m_vDirection.Normalized();
	pos = pos + m_vDirection * m_fSpeed * g_fSPF;

	if (pos.x > 800.0f) {
		pos.x = 800.0f;
		m_vDirection.x *= -1.0f;
	}
	if (pos.x < 0.0f) {
		pos.x = 0.0f;
		m_vDirection.x *= -1.0f;
	}
	if (pos.y > 600.0f) {
		pos.y = 600.0f;
		m_vDirection.y *= -1.0f;
	}
	if (pos.y < 0.0f) {
		pos.y = 0.0f;
		m_vDirection.y *= -1.0f;
	}
	SetPosition(pos);
}
ANpc::ANpc(std::wstring name) : ANpcCharacter(name)
{
	
}
ANpc::ANpc()
{
}
ANpc::~ANpc()
{

}



void	ANpcFsm::Init()
{
	m_pFsm = &(TNpcManager::FSM());
}