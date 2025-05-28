#include "Sample.h"
//ID3D11Texture2D* m_pTexture = nullptr;
//ID3D11ShaderResourceView* m_pSRV = nullptr;

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
                p.second->Render();
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

     // 한글 출력
    std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    std::wstring name = L"Background";
    name += std::to_wstring(0);// 정수가 스크링이 된다.
    auto actor = std::make_shared<UBackground>(name);
    if (actor->Create({ 0.0f, 0.0f }, { 800.0f,600.0f },
        L"../../data/texture/kgcabk.bmp",
        L"../../data/shader/DefaultShader.txt"))
    {
        m_World.m_ActorList.insert(std::make_pair(name, actor));
    }

    for (int i = 0; i < 10; i++)
    {
        TString name = L"UUI";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto actor = std::make_shared<UUI1>(name);
        TString texPath = L"../../data/texture/";
        texPath += std::to_wstring(i);
        texPath += L".png";
        if (actor->Create({ i * 80.0f + 5.0f, 10.0f }, { 70.0f,50.0f },
            texPath, L"../../data/shader/DefaultShader.txt"))
        {
            m_World.m_ActorList.insert(std::make_pair(name, actor));
        }
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

    name.clear();
    name = L"Player";    
    m_Player = std::make_shared<UBackground>(name);
    m_Player->SetName(name);
    // 400, 300
    // v0(90,1) ~ v1(133,63)
    float v0u = 91.0f / 400.0f;
    float v0v = 2.0f / 300.0f;
    float v1u = 131.0f/ 400.0f; 
    float v1v = 60.0f / 300.0f;
    if (m_Player->Create({ 400.0f, 300.0f }, { 43.0f,62.0f },
        L"../../data/texture/bitmap1Alpha.bmp", 
        L"../../data/shader/DefaultShader.txt"))
    {        
        m_Player->m_VertexList[0].t = { v0u, v0v };
        m_Player->m_VertexList[1].t = { v1u, v0v };
        m_Player->m_VertexList[2].t = { v0u, v1v };
        m_Player->m_VertexList[5].t = { v1u, v1v };
        m_Player->m_VertexList[3].t = m_Player->m_VertexList[2].t;
        m_Player->m_VertexList[4].t = m_Player->m_VertexList[1].t;
        m_Player->UpdateVertexBuffer();
        

        m_World.m_ActorList.insert(std::make_pair(name, m_Player));
    }

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
    if (m_Input->GetKey('W') == KEY_HOLD)
    {        
        m_Player->Move(0.0f, -1.0f);
    }
    if (m_Input->GetKey('S') == KEY_HOLD)
    {        
        m_Player->Move(0.0f, 1.0f);
    }
    if (m_Input->GetKey('A') == KEY_HOLD)
    {        
        m_Player->Move(-1.0f, 0.0f);
    }
    if (m_Input->GetKey('D') == KEY_HOLD)
    {       
        m_Player->Move(1.0f, 0.0f);
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