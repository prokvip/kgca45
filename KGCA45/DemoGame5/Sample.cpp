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
            m_MapObj->Tick();                               
            m_Player->Tick();
            for (auto& p : m_World.m_ActorList)
            {
                if (p.second->m_bDraw == false)
                {
                    continue;
                }
                p.second->Tick();
            }
            m_TimerObj.Tick();    
            m_EffectObj.Tick();
            m_World.Tick();

            m_MapObj->Render();
            m_Player->Render();
            for (auto& p : m_World.m_ActorList)
            {
                if (p.second->m_bDraw == false)
                {
                    continue;
                }
                p.second->Render();
            }
            m_TimerObj.Render();
            m_EffectObj.Render();

            m_World.Render();
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
    m_MapObj = std::make_shared<UBackground>(name);
    if (m_MapObj->Create({ 0.0f, 0.0f }, { 800.0f,600.0f },
        L"../../data/texture/kgcabk.bmp",
        L"../../data/shader/DefaultShader.txt"))
    {       
    }

    
    UWorld::g_listA.reserve(10);
    for (int i = 0; i < 10; i++)
    {
        TString texPath = L"../../data/texture/";
        texPath += std::to_wstring(i);
        texPath += L".png";
        UWorld::g_listA.emplace_back(texPath);
    }
    UWorld::g_listB.reserve(10);
    for (int i = 0; i < 10; i++)
    {
        TString texPath = L"../../data/texture/lot_wik0";
        texPath += std::to_wstring(i);
        texPath += L".dds";
        UWorld::g_listB.emplace_back(texPath);
    }

    if (m_TimerObj.Create({ 700.0f, 0.0f }, { 50.0f,50.0f },
        L"../../data/texture/0.png",
        L"../../data/shader/DefaultShader.txt"))
    {       
        m_TimerObj.SetTextureList(UWorld::g_listA);
    }
    if (m_EffectObj.Create({ 400.0f, 0.0f }, { 100.0f,100.0f },
        L"../../data/texture/get_item_03.dds",
        L"../../data/shader/DefaultShader.txt"))
    {
    }
        
    for (int i = 0; i < 10; i++)
    {
        TString name = L"NPC";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<UNpc>(name);
        TString texPath = L"../../data/texture/";
        texPath += std::to_wstring(i);
        texPath += L".png";
      /*  if (npc->Create(
            { i * 80.0f + 5.0f, 500.0f },
            { 70.0f,50.0f },*/
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ x, y },{ 70.0f,50.0f },
            texPath, L"../../data/shader/DefaultShader.txt"))
        {
            m_World.m_ActorList.insert(std::make_pair(name, npc));
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
    m_Player = std::make_shared<UPlayer>(name);
    m_Player->SetName(name);

    if (m_Player->Create({ 400.0f, 300.0f }, { 43.0f,62.0f },
        L"../../data/texture/bitmap1Alpha.bmp", 
        L"../../data/shader/DefaultShader.txt"))
    {        
        TVector2 p = {91.0f, 2.0f};
        TVector2 s = {40.0f, 58.0f};
        m_Player->UpdateUVVertexData(p,s);
        m_Player->UpdateVertexBuffer();         
    }
    m_World.m_pPlayer = m_Player;

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