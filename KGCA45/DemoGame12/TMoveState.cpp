#include "TMoveState.h"
#include "ANpc.h"
#include "TNpcManager.h"
void TMoveState::Process(APawn* pPlayer)
{   
    m_Timer += g_fSPF;
	TVector2 pos = m_pOwner->GetPosition();
	m_pOwner->Movement();	
    if (m_Timer > 10.0f)
    {
       
        int iOutput = m_pOwner->m_pMgr->GetFsm(m_pOwner->m_iPatternType).GetTransition(
            STATE_MOVE,
            EVENT_TIMEOUT);
        if (iOutput >= 0)
        {
            m_Timer = 0.0f;
            m_pOwner->m_pCurrentState = m_pOwner->m_pMgr->GetPattern(m_pOwner->m_iPatternType).m_StateList[iOutput].get();
            P(L"\n%s", L"TStopState::EVENT_TIMEOUT -> STATE_STOP");
        }
    }

    TVector2 npc = m_pOwner->GetPosition();
    TVector2 play = pPlayer->GetPosition();
    float fDistance = (play - npc).length();
    if (fDistance < 200.0f)
    {
        int iOutput = m_pOwner->m_pMgr->GetFsm(m_pOwner->m_iPatternType).GetTransition(
            STATE_MOVE,
            EVENT_FINDTARGET);
        if (iOutput >= 0)
        {
            m_Timer = 0.0f;
            m_pOwner->m_pCurrentState = m_pOwner->m_pMgr->GetPattern(m_pOwner->m_iPatternType).m_StateList[iOutput].get();
            P(L"\n%s", L"TAttackState::EVENT_FINDTARGET -> STATE_ATTACK");
        }
    }
}
TMoveState::TMoveState(ANpc* pOwner) : TObjectState(pOwner)
{

}