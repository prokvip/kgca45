#include "Sample.h"
LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
    /*switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        int kk = 0;
    }break;
    }*/
    TWindow::MsgProc(hWnd, message, wParam, lParam);
    return 1;
}
void Sample::GameRun()
{
    for (auto pNode = m_CompList.begin();pNode != m_CompList.end();pNode++)
    {
        (*pNode)->TickComponent();
    }
    if (GameLoop())
    {  
        m_dxDevice.PreRender();
            for (auto& p : m_World.m_ActorList)
            {
                p.second->Tick();
                p.second->Show();
            }
        m_dxDevice.PostRender();
    }	
}
void Sample::InitGame()
{
    P(L"%s\n", L"Create DirectX  : true");
    m_dxDevice.CreateDevice(GetHwnd());
    m_dxDevice.CreateRenderTargetView();
    m_dxDevice.SetViewPort();
    // �ѱ� ���
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    std::wstring name = L"Background";
    name += std::to_wstring(0);// ������ ��ũ���� �ȴ�.
    auto actor = std::make_shared<UBackground>(name);
    actor->SetRect({ 0.0f, 0.0f }, { 800.0f,600.0f });
    actor->CreateVertexData();
    actor->CreateVertexBuffer();

    actor->CreateVertexShader();
    actor->CreatePixelShader();
    actor->CreateVertexLayout();
    m_World.m_ActorList.insert(std::make_pair(name, actor));

    //for (int i = 0; i < 8; i++)
    //{
    //    std::wstring name = L"UUI";
    //    name += std::to_wstring(i);// ������ ��ũ���� �ȴ�.
    //    auto actor = std::make_shared<UUI1>(name);
    //    actor->SetRect({ i*100.0f+10.0f, 10.0f }, { 80.0f,50.0f });
    //    
    //    actor->CreateVertexData();
    //    actor->CreateVertexBuffer();   

    //    actor->CreateVertexShader();
    //    actor->CreatePixelShader();
    //    actor->CreateVertexLayout();
    //    m_World.m_ActorList.insert(std::make_pair(name, actor));
    //}

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    // ���ӻ���
    using CompPtr = std::shared_ptr<UActorComponent>;
    m_CompList.push_back(std::make_shared<UTimerComponent>(L"GameTimer"));
    m_Timer = std::dynamic_pointer_cast<UTimerComponent>(m_CompList.back());

    m_CompList.push_back(std::make_shared<UInputComponent>(L"GameInput"));
    m_Input = std::dynamic_pointer_cast<UInputComponent>(m_CompList.back());

    m_CompList.push_back(std::make_shared <USoundComponent>(L"GameSound"));

    if (m_Timer == nullptr)
    {
        m_CompList.clear();
        return;
    }
}
bool Sample::GameLoop()
{
    if (m_Input->GetKey('W') == KEY_PUSH)
    {        
        m_Player->Move(0.0f, -1.0f);
        m_Player->Show();
    }
    if (m_Input->GetKey('S') == KEY_PUSH)
    {        
        m_Player->Move(0.0f, 1.0f);
        m_Player->Show();
    }
    if (m_Input->GetKey('A') == KEY_PUSH)
    {        
        m_Player->Move(-1.0f, 0.0f);
        m_Player->Show();
    }
    if (m_Input->GetKey('D') == KEY_PUSH)
    {       
        m_Player->Move(1.0f, 0.0f);
        m_Player->Show();
    }
   
    for (auto& p : m_World.m_ActorList)
    {
        p.second->Tick();
        //p.second->Show();
    }
    return true;
}
void Sample::ReleaseGame()
{
    P(L"\n%s", L"Release DirectX  : true");
    m_dxDevice.Release();

    std::wcout << std::endl;
    std::wcout << m_Timer->GetGameGlobalTimer() << std::endl;

    m_CompList.clear();
    m_World.m_ActorList.clear();

    std::wcout << L"���� �ν��Ͻ� ���� : " << UActorComponent::GetNumInstance() << std::endl;
}