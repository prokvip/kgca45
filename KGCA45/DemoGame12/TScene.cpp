#include "TScene.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"

#include "TIntroScene.h"
#include "TLobbyScene.h"
#include "TGameScene.h"
#include "TResultScene.h"


LRESULT TScene::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return 1;
}
void TScene::InitScene()
{ 
}
void TScene::Frame()
{   
}
void TScene::Render()
{   
}
void TScene::ReleaseScene()
{   
}

TScene::TScene(TSceneManager* pOwnder)
{
	m_pOwner = pOwnder;
}
TScene::~TScene()
{

}

void TSceneManager::Frame()
{
	m_pCurrentScene->Process(nullptr);
	m_pCurrentScene->Frame();
}
void TSceneManager::Render()
{
	m_pCurrentScene->Render();
}
void TSceneManager::Init()
{
	m_pIntroScene = std::make_shared<TIntroScene>(this);
	m_pLobbyScene = std::make_shared<TLobbyScene>(this);
	m_pInGameScene = std::make_shared<TGameScene>(this);
	m_pResultScene = std::make_shared<TResultScene>(this);
	m_SceneList.emplace_back(m_pIntroScene);
	m_SceneList.emplace_back(m_pLobbyScene);
	m_SceneList.emplace_back(m_pInGameScene);
	m_SceneList.emplace_back(m_pResultScene);

	m_pIntroScene->InitScene();
	m_pLobbyScene->InitScene();
	m_pInGameScene->InitScene();
	m_pResultScene->InitScene();

	m_pCurrentScene = m_pIntroScene.get();

	// 상태 구조 초기화
  // 현상태            -> 이벤트           -> 상태전환
// TSCENE_STATE_INTRO->TSCENE_EVENT_ENTER   ->TSCENE_STATE_LOBBY
// TSCENE_STATE_INTRO->TSCENE_EVENT_TIMEOUT ->TSCENE_STATE_LOBBY
// 
// TSCENE_STATE_LOBBY->TSCENE_EVENT_ENTER->TSCENE_STATE_INGAME
// TSCENE_STATE_LOBBY->TSCENE_EVENT_START->TSCENE_STATE_INGAME
// 
// TSCENE_STATE_INGAME->TSCENE_EVENT_ENTER    ->TSCENE_STATE_RESULT
// TSCENE_STATE_INGAME->TSCENE_EVENT_TIMEOUT  ->TSCENE_STATE_RESULT
// TSCENE_STATE_INGAME->TSCENE_EVENT_END      ->TSCENE_STATE_RESULT
// TSCENE_STATE_INGAME->TSCENE_EVENT_RESTART  ->TSCENE_STATE_INGAME
// TSCENE_STATE_INGAME->TSCENE_EVENT_EXIT     ->TSCENE_STATE_LOBBY

// TSCENE_STATE_RESULT->TSCENE_EVENT_ENTER  ->TSCENE_STATE_LOBBY
// TSCENE_STATE_RESULT->TSCENE_EVENT_RESTART->TSCENE_STATE_INGAME

	m_pFsm.AddStateTransition(TSCENE_STATE_INTRO,
		TSCENE_EVENT_ENTER,
		TSCENE_STATE_LOBBY);
	m_pFsm.AddStateTransition(TSCENE_STATE_INTRO,
		TSCENE_EVENT_TIMEOUT,
		TSCENE_STATE_LOBBY);
	m_pFsm.AddStateTransition(TSCENE_STATE_LOBBY,
		TSCENE_EVENT_ENTER,
		TSCENE_STATE_INGAME);
	m_pFsm.AddStateTransition(TSCENE_STATE_INGAME,
		TSCENE_EVENT_ENTER,
		TSCENE_STATE_RESULT);
	m_pFsm.AddStateTransition(TSCENE_STATE_INGAME,
		TSCENE_EVENT_TIMEOUT,
		TSCENE_STATE_RESULT);
	m_pFsm.AddStateTransition(TSCENE_STATE_INGAME,
		TSCENE_EVENT_END,
		TSCENE_STATE_RESULT);
	m_pFsm.AddStateTransition(TSCENE_STATE_RESULT,
		TSCENE_EVENT_ENTER,
		TSCENE_STATE_LOBBY);
}
TSceneManager::TSceneManager()
{
}
TSceneManager::~TSceneManager()
{
	if (m_pIntroScene)m_pIntroScene->ReleaseScene();
	if (m_pLobbyScene)m_pLobbyScene->ReleaseScene();
	if (m_pInGameScene)m_pInGameScene->ReleaseScene();
	if (m_pResultScene)m_pResultScene->ReleaseScene();
}