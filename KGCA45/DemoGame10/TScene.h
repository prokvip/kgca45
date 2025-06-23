#pragma once
#include "UWorld.h"
#include "TWindow.h"
#include "TDevice.h"
#include "TSound.h"
class UPawn;
class TScene;
// fsm
class TSceneManager : public UObject
{
public:
	TScene* m_pCurrentScene = nullptr;
	std::shared_ptr<TScene> m_pIntroScene = nullptr;
	std::shared_ptr<TScene> m_pLobbyScene = nullptr;
	std::shared_ptr<TScene> m_pInGameScene = nullptr;
	std::shared_ptr<TScene> m_pResultScene = nullptr;
	std::vector<std::shared_ptr<TScene>> m_SceneList;
	virtual void Init();
	virtual void Frame();
	virtual void Render();
	TSceneManager();
	virtual ~TSceneManager();
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
	virtual void Frame();
	virtual void Render();
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	TScene(TSceneManager* pOwnder);
	virtual ~TScene();
};