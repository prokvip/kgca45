#include "TSceneFSM.h"
void TSceneState::AddTransition(ESceneEvent event, ESceneState outState)
{
	this->m_events.insert(
		std::make_pair(event, outState));
}
int TSceneState::GetTransition(ESceneEvent event)
{
	if( m_events.find(event) != m_events.end())
	{
		return m_events[event];
	}
	return -1;
}
void TSceneFSM::AddStateTransition(
	ESceneState inState , 
	ESceneEvent  event, 
	ESceneState outState)
{
	TSceneState* pState = nullptr;	
	if (m_states.find(inState) != m_states.end())
	{
		pState = m_states[inState];
	}
	else
	{
		pState = new TSceneState(inState);
	}
	pState->AddTransition(event, outState);
	m_states.insert(
		std::make_pair(inState, pState));
}

int TSceneFSM::GetTransition(	ESceneState currentState, 
								ESceneEvent event)
{
	auto it = m_states.find(currentState);
	if (it != m_states.end())
	{
		return it->second->GetTransition(event);
	}
	return -1; // 상태전환이 없는 경우
}