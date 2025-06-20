#include "Sample.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"

LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
    if (m_pCurrentScene)
    {
        m_pCurrentScene->MsgProc(hWnd, message, wParam, lParam);
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

    m_pCurrentScene->Frame();

	m_dxDevice.PreRender(); // 렌더링 준비
        m_pCurrentScene->Render();
    m_dxDevice.PostRender(); // 렌더링 준비

    TSound::UpdateSystem(); // 사운드 업데이트

    if (TEngine::gInput->GetKey(VK_RETURN) == KEY_PUSH)
    {
        if(m_pCurrentScene == m_pIntroScene.get())
        {
			m_pLobbyScene->ReleaseScene();
			m_pLobbyScene.reset(new TLobbyScene());
			m_pLobbyScene->InitScene();
            m_pCurrentScene = m_pLobbyScene.get();
        }
        else if (m_pCurrentScene == m_pLobbyScene.get())
        {
            m_pInGameScene->ReleaseScene();
            m_pInGameScene.reset(new TGameScene());
            m_pInGameScene->InitScene();
            m_pCurrentScene = m_pInGameScene.get();
        }
        else if (m_pCurrentScene == m_pInGameScene.get())
        {
            m_pResultScene->ReleaseScene();
            m_pResultScene.reset(new TResultScene());
            m_pResultScene->InitScene();
            m_pCurrentScene = m_pResultScene.get();
        }
        else if (m_pCurrentScene == m_pResultScene.get())
        {
            m_pLobbyScene->ReleaseScene();
            m_pLobbyScene.reset(new TLobbyScene());
            m_pLobbyScene->InitScene();
            m_pCurrentScene = m_pLobbyScene.get();
		}        
    }
}
void Sample::InitGame()
{
   // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");
    P(L"%s\n", L"Create DirectX  : true");
    m_dxDevice.CreateDevice(GetHwnd());
    m_dxDevice.CreateRenderTargetView();
    m_dxDevice.SetViewPort();      
    
    m_Engine.Init();

	m_pIntroScene = std::make_shared<TIntroScene>();
    m_pLobbyScene = std::make_shared<TLobbyScene>();
    m_pInGameScene = std::make_shared<TGameScene>();
    m_pResultScene = std::make_shared<TResultScene>();
	m_pIntroScene->InitScene();
    m_pLobbyScene->InitScene();
    m_pInGameScene->InitScene();
    m_pResultScene->InitScene();

    m_pCurrentScene = m_pIntroScene.get();
}
void Sample::ReleaseGame()
{
    P(L"\n%s", L"Release DirectX  : true");  
    m_pIntroScene->ReleaseScene();
    m_pLobbyScene->ReleaseScene();
    m_pInGameScene->ReleaseScene();
    m_pResultScene->ReleaseScene();

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
