#pragma once
#include "UWorld.h"
#include "TWindow.h"
#include "TDevice.h"
#include "TSound.h"
#include "TFsm.h"

class UPawn;
class TSceneManager;

struct TSceneStateEvent
{ 
	enum  ESceneState
	{
		TSCENE_STATE_INTRO = 0,
		TSCENE_STATE_LOBBY,
		TSCENE_STATE_INGAME,
		TSCENE_STATE_RESULT,
		TSCENE_STATE_COUNTER,
	};
	enum  ESceneEvent
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
};
class TScene : public UObject
{
public:
	TSceneManager*  m_pOwner = nullptr;
	float			m_Timer = 0.0f; // 프레임 시간
public:
	std::shared_ptr<AActor>				m_MapObj = nullptr;
	std::shared_ptr<ATimerEffect>		m_TimerObj = nullptr;
	std::shared_ptr<AActor>				m_EffectObj = nullptr;
	std::vector<TSound*>				m_Soundlist;
	std::shared_ptr<UWorld>				m_World;
	std::shared_ptr<APlayerCharacter>	m_Player = nullptr;
public:
	virtual void InitScene();
	virtual void ReleaseScene();
	// 상태전환 프레임
	virtual void Process(UPawn* pPlayer) = 0;
	virtual void Init() {};
	virtual void Tick();
	virtual void Render();
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	TScene(TSceneManager* pOwnder);
	virtual ~TScene();
};

// fsm
class TSceneManager : public UObject
{
public:
	TFsm<TSceneStateEvent>	m_Fsm; // 상태머신
	TSceneStateEvent& GetDefinition()
	{
		return m_Fsm.Definition;
	}
	TScene* m_pCurrentScene = nullptr;
	std::shared_ptr<TScene> m_pIntroScene = nullptr;
	std::shared_ptr<TScene> m_pLobbyScene = nullptr;
	std::shared_ptr<TScene> m_pInGameScene = nullptr;
	std::shared_ptr<TScene> m_pResultScene = nullptr;
	std::vector<std::shared_ptr<TScene>> m_SceneList;
	virtual void Init();
	virtual void Tick();
	virtual void Render();
	TSceneManager();
	virtual ~TSceneManager();
};