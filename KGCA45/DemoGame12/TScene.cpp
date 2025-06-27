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
void TScene::Tick()
{   
}
void TScene::Render()
{   
}
void TScene::ReleaseScene()
{   
}
void TScene::SceneChange(int iScene, int iEvent )
{
	/*m_pLobbyScene->ReleaseScene();
	m_pLobbyScene.reset(new TLobbyScene());
	m_pLobbyScene->InitScene();*/
	UWorld::m_vCameraPos = { g_rtClient.right * 0.5f, g_rtClient.bottom * 0.5f };
	int iOutput = m_pOwner->m_pFsm.GetTransition(
		iScene,
		iEvent);
	m_pOwner->m_pCurrentScene = m_pOwner->m_SceneList[iOutput].get();
}
void TScene::Scroll()
{
	//TVector2 cam = { 400.0f, 300.0f };
	//cam.x += cosf(g_fGameTimer) * 400.0f;

	TVector2 cam = UWorld::m_vCameraPos;
	cam.x += g_fSPF * 50.0f;
	if (TEngine::gInput->GetKey('D') == KEY_HOLD)
	{
		cam.x += g_fSPF * 100.0f;
	}
	if (TEngine::gInput->GetKey('A') == KEY_HOLD)
	{
		cam.x -= g_fSPF * 100.0f;
	}
	if (TEngine::gInput->GetKey('W') == KEY_HOLD)
	{
		cam.y -= g_fSPF * 100.0f;
	}
	if (TEngine::gInput->GetKey('S') == KEY_HOLD)
	{
		cam.y += g_fSPF * 100.0f;
	}
	m_World->m_vCameraPos = cam;	
}
void TScene::FadeOut(AActor* actor)
{
	actor->m_fAlpha -= g_fSPF * 0.33f;
	if (actor->m_fAlpha < 0.0f) actor->m_fAlpha = 0.0f;
}
void TScene::FadeIn(AActor* actor)
{
	actor->m_fAlpha += g_fSPF*0.33f;
	if (actor->m_fAlpha > 1.0f) actor->m_fAlpha = 1.0f;
}
TScene::TScene(TSceneManager* pOwnder)
{
	m_pOwner = pOwnder;
}
TScene::~TScene()
{

}

void TSceneManager::Tick()
{
	m_pCurrentScene->Process(nullptr);
	m_pCurrentScene->Tick();
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

	m_pFsm.AddStateTransition(TSCENE_STATE_INTRO,TSCENE_EVENT_ENTER,TSCENE_STATE_LOBBY);
	m_pFsm.AddStateTransition(TSCENE_STATE_INTRO,TSCENE_EVENT_TIMEOUT,TSCENE_STATE_LOBBY);
	m_pFsm.AddStateTransition(TSCENE_STATE_LOBBY,TSCENE_EVENT_ENTER,TSCENE_STATE_INGAME);
	m_pFsm.AddStateTransition(TSCENE_STATE_LOBBY,TSCENE_EVENT_START,TSCENE_STATE_INGAME);
	m_pFsm.AddStateTransition(TSCENE_STATE_INGAME,TSCENE_EVENT_ENTER,TSCENE_STATE_RESULT);
	m_pFsm.AddStateTransition(TSCENE_STATE_INGAME,TSCENE_EVENT_TIMEOUT,	TSCENE_STATE_RESULT);
	m_pFsm.AddStateTransition(TSCENE_STATE_INGAME,TSCENE_EVENT_END,	TSCENE_STATE_RESULT);
	m_pFsm.AddStateTransition(TSCENE_STATE_RESULT,TSCENE_EVENT_ENTER,TSCENE_STATE_LOBBY);
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