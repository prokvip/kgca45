#include "TStopState.h"
#include "ANpc.h"
#include "APawn.h"
#include "TEngine.h"
#include "TNpcManager.h"
void TStopState::Process(APawn* pPlayer)
{
    m_Timer += g_fSPF;
    TVector2 npc = m_pOwner->GetPosition();
    TVector2 play = pPlayer->GetPosition();
    float fDistance = (play - npc).length();
    if (fDistance < 200.0f)
    {       
        int iOutput = m_pOwner->m_pMgr->GetFsm(m_pOwner->m_iPatternType).GetTransition(
            STATE_STOP,
            EVENT_FINDTARGET);
        if (iOutput >= 0)
        {
            m_Timer = 0.0f;
            m_pOwner->m_pCurrentState = m_pOwner->m_pMgr->GetPattern(m_pOwner->m_iPatternType).m_StateList[iOutput].get();
            P(L"\n%s", L"TAttackState::EVENT_FINDTARGET ->STATE_ATTACK");
        }
    }
    if (m_Timer > 3.0f)
    {
       
        int iOutput = m_pOwner->m_pMgr->GetFsm(m_pOwner->m_iPatternType).GetTransition(
            STATE_STOP,
            EVENT_TIMEOUT);
        if (iOutput >= 0)
        {
            m_Timer = 0.0f;
            m_pOwner->m_pCurrentState = m_pOwner->m_pMgr->GetPattern(m_pOwner->m_iPatternType).m_StateList[iOutput].get();
            P(L"\n%s", L"TMoveState::EVENT_TIMEOUT ->STATE_MOVE");
        }
    }
}
TStopState::TStopState(ANpc* pOwner) : TObjectState(pOwner)
{

}