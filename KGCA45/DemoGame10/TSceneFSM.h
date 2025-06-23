#pragma once
#include "TStd.h"

enum  ESceneState
{
	TSCENE_STATE_INTRO=0,
	TSCENE_STATE_LOBBY,
	TSCENE_STATE_INGAME,
	TSCENE_STATE_RESULT,
	TSCENE_STATE_COUNTER,
};
enum class ESceneEvent
{
	TSCENE_EVENT_ENTER = 0,
	TSCENE_EVENT_TIMEOUT,

	TSCENE_EVENT_START,
	TSCENE_EVENT_END,
	TSCENE_EVENT_NEXT,
	TSCENE_EVENT_PREV,
	TSCENE_EVENT_PAUSE,
	TSCENE_EVENT_RESUME,
	TSCENE_EVENT_RESTART,
	TSCENE_EVENT_EXIT,
};
// 현상태            -> 이벤트           -> 상태전환
// TSCENE_STATE_INTRO->TSCENE_EVENT_ENTER   ->TSCENE_STATE_LOBBY
// TSCENE_STATE_INTRO->TSCENE_EVENT_TIMEOUT ->TSCENE_STATE_LOBBY
// 
// TSCENE_STATE_LOBBY->TSCENE_EVENT_ENTER->TSCENE_STATE_INGAME
// TSCENE_STATE_LOBBY->TSCENE_EVENT_START->TSCENE_STATE_INGAME
// 
// TSCENE_STATE_INGAME->TSCENE_EVENT_ENTER    ->TSCENE_STATE_RESULT
// TSCENE_STATE_INGAME->TSCENE_EVENT_END      ->TSCENE_STATE_RESULT
// TSCENE_STATE_INGAME->TSCENE_EVENT_RESTART  ->TSCENE_STATE_INGAME
// TSCENE_STATE_INGAME->TSCENE_EVENT_EXIT     ->TSCENE_STATE_LOBBY
 
// TSCENE_STATE_RESULT->TSCENE_EVENT_ENTER  ->TSCENE_STATE_LOBBY
// TSCENE_STATE_RESULT->TSCENE_EVENT_RESTART->TSCENE_STATE_INGAME
class TSceneState
{
	std::map<ESceneEvent, ESceneState> m_events;
	int   m_iStateID; // 상태 ID
public:
	void		AddTransition(ESceneEvent event, ESceneState outState);
	int			GetTransition(ESceneEvent event);
	TSceneState(int iState) : m_iStateID(iState) {}
};
class TSceneFSM
{
	std::map<ESceneState, TSceneState*> m_states;
public:
	// 싱글톤패턴(singleton pattern)으로 구현
	static TSceneFSM& GetInstance()
	{
		static TSceneFSM instance;
		return instance;
	}
	// 상태객체 및 이벤트 추가
	void AddStateTransition(ESceneState, ESceneEvent, ESceneState);
	// 현재 이벤트에 대한 상태전환을 반환
	int GetTransition(ESceneState currentState, ESceneEvent event);
private:
	TSceneFSM() {};
};

#define IScene TSceneFSM::GetInstance()