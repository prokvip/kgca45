#include "TStopState.h"
#include "ANpc.h"
#include "APawn.h"
#include "TEngine.h"
void TStopState::Process(APawn* pPlayer)
{
    m_Timer += g_fSPF;
    TVector2 npc = m_pOwner->GetPosition();
    TVector2 play = pPlayer->GetPosition();
    float fDistance = (play - npc).length();
    if (fDistance < 200.0f)
    {
        m_Timer = 0.0f;
        int iOutput = m_pOwner->m_Fsm.GetTransition(
            m_pOwner->GetDefinition().STATE_STOP,
            m_pOwner->GetDefinition().EVENT_FINDTARGET);
        m_pOwner->m_pCurrentState = m_pOwner->m_StateList[iOutput].get();
        P(L"\n%s", L"TAttackState::EVENT_FINDTARGET Transition");
    }
    if (m_Timer > 3.0f)
    {
        m_Timer = 0.0f;
        int iOutput = m_pOwner->m_Fsm.GetTransition(
            m_pOwner->GetDefinition().STATE_STOP,
            m_pOwner->GetDefinition().EVENT_TIMEOUT);
        m_pOwner->m_pCurrentState = m_pOwner->m_StateList[iOutput].get();
        P(L"\n%s", L"TMoveState::EVENT_TIMEOUT TRansition");
    }
}
TStopState::TStopState(ANpc* pOwner) : TObjectState(pOwner)
{

}