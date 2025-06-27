#include "Sample.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "TFsm.h"
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
    m_Engine.Tick();
    m_SceneManager.Tick();

	m_dxDevice.PreRender(); // ������ �غ�
        m_SceneManager.Render();
    m_dxDevice.PostRender(); // ������ �غ�    
}
void Sample::InitGame()
{
    // �ѱ� ���
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");
    P(L"%s\n", L"Create DirectX  : true");
    m_dxDevice.CreateDevice(GetHwnd());
    m_dxDevice.CreateRenderTargetView();
    m_dxDevice.SetViewPort();      
  
    m_Engine.Init();	
    m_SceneManager.Init();    
}
void Sample::ReleaseGame()
{
    P(L"\n%s", L"Release DirectX  : true");  
    m_dxDevice.Release();   
    std::wcout << std::endl;
    std::wcout << TEngine::gTimer->GetGameGlobalTimer() << std::endl;
    std::wcout << L"���� �ν��Ͻ� ���� : " << UActorComponent::GetNumInstance() << std::endl;
}
int main()
{
    Sample game;
    game.SetWindow(GetModuleHandle(nullptr));
    game.InitGame();
    game.Run();
    game.ReleaseGame();
}
