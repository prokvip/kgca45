#include "ANpc.h"
#include "TAttackState.h"
#include "TStopState.h"
#include "TMoveState.h"
#include "UWorld.h"
#include "TNpcManager.h"
void   ANpc::Init()
{
	m_pCurrentState = m_pMgr->GetPattern(m_iPatternType).m_StateList[STATE_STOP].get();
}
void	ANpc::Tick()
{
	if (m_pCurrentState)
	{
		m_pCurrentState->m_pOwner = this;
		m_pCurrentState->Process((APawn*)UWorld::m_pPlayer.get());
	}
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

