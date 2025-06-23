#include "Sample.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "TSceneFSM.h"
LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
    if (m_SceneManager.m_pCurrentScene)
    {
        m_SceneManager.m_pCurrentScene->MsgProc(hWnd, message, wParam, lParam);
    }
    TWindow::MsgProc(hWnd, message, wParam, lParam);
    return 1;
}
void Sample::GameRun()
{
    for (auto pNode = m_Engine.m_CompList.begin(); pNode != m_Engine.m_CompList.end(); pNode++)
    {
        (*pNode)->TickComponent();
    }

    m_SceneManager.Frame();

	m_dxDevice.PreRender(); // 렌더링 준비
        m_SceneManager.Render();
    m_dxDevice.PostRender(); // 렌더링 준비

    TSound::UpdateSystem(); // 사운드 업데이트

   
  //  if (TEngine::gInput->GetKey(VK_RETURN) == KEY_PUSH)
  //  {
  //      if(m_pCurrentScene == m_pIntroScene.get())
  //      {
		//	/*m_pLobbyScene->ReleaseScene();
		//	m_pLobbyScene.reset(new TLobbyScene());
		//	m_pLobbyScene->InitScene();*/
  //          m_pCurrentScene = m_pLobbyScene.get();
  //      }
  //      else if (m_pCurrentScene == m_pLobbyScene.get())
  //      {
  //          m_pInGameScene->ReleaseScene();
  //          m_pInGameScene.reset(new TGameScene());
  //          m_pInGameScene->InitScene();
  //          m_pCurrentScene = m_pInGameScene.get();
  //      }
  //      else if (m_pCurrentScene == m_pInGameScene.get())
  //      {
  //        /*  m_pResultScene->ReleaseScene();
  //          m_pResultScene.reset(new TResultScene());
  //          m_pResultScene->InitScene();*/
  //          m_pCurrentScene = m_pResultScene.get();
  //      }
  //      else if (m_pCurrentScene == m_pResultScene.get())
  //      {
  //          /*m_pLobbyScene->ReleaseScene();
  //          m_pLobbyScene.reset(new TLobbyScene());
  //          m_pLobbyScene->InitScene();*/
  //          m_pCurrentScene = m_pLobbyScene.get();
		//}        
  //  }
}
void Sample::InitGame()
{
   // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");
    P(L"%s\n", L"Create DirectX  : true");
    m_dxDevice.CreateDevice(GetHwnd());
    m_dxDevice.CreateRenderTargetView();
    m_dxDevice.SetViewPort();      
    
    // 상태 구조 초기화
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

    IScene.AddStateTransition(  TSCENE_STATE_INTRO,
                                ESceneEvent::TSCENE_EVENT_ENTER, 
                                TSCENE_STATE_LOBBY);
    IScene.AddStateTransition(TSCENE_STATE_INTRO,
                                ESceneEvent::TSCENE_EVENT_TIMEOUT,
                                TSCENE_STATE_LOBBY);
    IScene.AddStateTransition(TSCENE_STATE_LOBBY,
                                ESceneEvent::TSCENE_EVENT_ENTER,
                                TSCENE_STATE_INGAME);
    IScene.AddStateTransition(TSCENE_STATE_INGAME,
                                ESceneEvent::TSCENE_EVENT_ENTER,
                                TSCENE_STATE_RESULT);
    IScene.AddStateTransition(TSCENE_STATE_INGAME,
                                ESceneEvent::TSCENE_EVENT_TIMEOUT,
                                TSCENE_STATE_RESULT);
    IScene.AddStateTransition(TSCENE_STATE_RESULT,
                                ESceneEvent::TSCENE_EVENT_ENTER,
                                TSCENE_STATE_LOBBY);
    m_Engine.Init();	
    m_SceneManager.Init();
}
void Sample::ReleaseGame()
{
    P(L"\n%s", L"Release DirectX  : true");  
    m_dxDevice.Release();   
    std::wcout << std::endl;
    std::wcout << TEngine::gTimer->GetGameGlobalTimer() << std::endl;
    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}
int main()
{
    Sample game;
    game.SetWindow(GetModuleHandle(nullptr));
    game.InitGame();
    game.Run();
    game.ReleaseGame();
}
