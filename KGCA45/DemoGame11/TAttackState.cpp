#include "TAttackState.h"
#include "ANpc.h"
#include "TNpcManager.h"
void TAttackState::Process(APawn* pPlayer)
{
    m_Timer += g_fSPF;
    TVector2 npc = m_pOwner->GetPosition();
    TVector2 play = pPlayer->GetPosition();
    float fDistance = (play - npc).length();
    if (fDistance > 300.0f)
    {
        m_Timer = 0.0f;
        int iOutput = m_pOwner->m_Fsm.GetTransition(
            m_pOwner->GetDefinition().STATE_ATTACK,
            m_pOwner->GetDefinition().EVENT_LOSTTARGET);
        m_pOwner->m_pCurrentState = m_pOwner->m_StateList[iOutput].get();
        P(L"\n%s", L"TMoveState::EVENT_LOSTTARGET Transition");
    }
    if (m_Timer > 3.0f)
    {
        m_Timer = 0.0f;
        int iOutput = m_pOwner->m_Fsm.GetTransition(
            m_pOwner->GetDefinition().STATE_ATTACK,
            m_pOwner->GetDefinition().EVENT_TIMEOUT);
        m_pOwner->m_pCurrentState = m_pOwner->m_StateList[iOutput].get();
        P(L"\n%s", L"TMoveState::EVENT_TIMEOUT TRansition");
    }
}
TAttackState::TAttackState(ANpc* pOwner) : TObjectState(pOwner)
{

}