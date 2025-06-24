#include "TMoveState.h"
#include "ANpc.h"
void TMoveState::Process(APawn* pPlayer)
{   
    m_Timer += g_fSPF;
	TVector2 pos = m_pOwner->GetPosition();
	m_pOwner->Movement();	
    if (m_Timer > 10.0f)
    {
        m_Timer = 0.0f;
        int iOutput = m_pOwner->m_Fsm.GetTransition(
            m_pOwner->GetDefinition().STATE_MOVE,
            m_pOwner->GetDefinition().EVENT_TIMEOUT);
        m_pOwner->m_pCurrentState = m_pOwner->m_StateList[iOutput].get();
        P(L"\n%s", L"TStopState::EVENT_TIMEOUT TRansition");
    }

    TVector2 npc = m_pOwner->GetPosition();
    TVector2 play = pPlayer->GetPosition();
    float fDistance = (play - npc).length();
    if (fDistance < 200.0f)
    {
        m_Timer = 0.0f;
        int iOutput = m_pOwner->m_Fsm.GetTransition(
            m_pOwner->GetDefinition().STATE_MOVE,
            m_pOwner->GetDefinition().EVENT_FINDTARGET);
        m_pOwner->m_pCurrentState = m_pOwner->m_StateList[iOutput].get();
        P(L"\n%s", L"TAttackState::EVENT_FINDTARGET Transition");
    }
}
TMoveState::TMoveState(ANpc* pOwner) : TObjectState(pOwner)
{

}