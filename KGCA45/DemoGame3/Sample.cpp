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
        m_dxDevice.Render();
    }	
}
void Sample::InitGame()
{
    P(L"%s\n", L"Create DirectX  : true");
    m_dxDevice.CreateDevice(GetHwnd());
    m_dxDevice.CreateRenderTargetView();

    // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    for (int i = 0; i < 1; i++)
    {
        std::wstring name = L"Background";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto actor = std::make_shared<UBackground>(name);
        actor->SetRect({ 0.0f, 0.0f }, { 800.0f,600.0f });
        actor->CreateVertexData();
        actor->CreateVertexBuffer();   

        actor->CreateVertexShader();
        actor->CreatePixelShader();
        actor->CreateVertexLayout();
        m_World.m_ActorList.insert(std::make_pair(name, actor));
    }
    //for (int i = 0; i < 1; i++)
    //{
    //    std::wstring name = L"APawn";
    //    name += std::to_wstring(i);// 정수가 스크링이 된다.
    //    auto pawn = std::make_shared<APawn>(name);
    //    pawn->SetName(name);
    //    pawn->SetRect({ 400.0f, 300.0f }, { 100.0f,100.0f });
    //    m_World.m_ActorList.insert(std::make_pair(name, pawn));
    //}
    //for (int i = 0; i < 1; i++)
    //{
    //    std::wstring name = L"ACharacer";
    //    name += std::to_wstring(i);// 정수가 스크링이 된다.
    //    auto character = std::make_shared<ACharacter>(name);
    //    character->SetName(name);
    //    character->SetRect({ 400.0f, 0.0f }, { 100.0f,100.0f });
    //    m_World.m_ActorList.insert( std::make_pair(name, character));
    //}

    //std::wstring name = L"Player";    
    //m_Player = std::make_shared<ACharacter>(name);
    //m_Player->SetName(name);
    //m_Player->SetRect({ 400.0f, 0.0f }, { 100.0f,100.0f });
    //m_World.m_ActorList.insert(std::make_pair(name, m_Player));

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
    // 게임생성
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

    std::wcout << L"현재 인스턴스 갯수 : " << UActorComponent::GetNumInstance() << std::endl;
}