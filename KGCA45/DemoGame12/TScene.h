#pragma once
#include "UWorld.h"
#include "TWindow.h"
#include "TDevice.h"
#include "TSound.h"
#include "TFsm.h"
#include "TNpcManager.h"

class APawn;
class TSceneManager;

enum T_CONTROL_STATE
{
	T_STATE_NORMAL = 0,
	T_STATE_MOUSEOVER,// HOVER
	T_STATE_PRESSED,  // PUSH
	T_STATE_SELECT,   // PUSH+UP

	T_STATE_DISABLED,
	T_STATE_HIDDEN,
	T_STATE_FOCUS,
	T_STATE_HOLD,       // HOLD
	
	T_STATE_MAXSTATE,
};

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
	virtual void Process(APawn* pPlayer) = 0;
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
	TFsm	m_pFsm; // 상태머신
	APlayerCharacter* GetPlayer()
	{
		return m_pCurrentScene->m_Player.get();
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