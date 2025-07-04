#include "Sample.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"

TAssetManager<TSound> Sample::g_SoundManager;

void Sample::TestFMOD()
{
    /// 사운드 테스트
    if (TEngine::gInput->GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        auto bgSound =
            Sample::g_SoundManager.GetAsset(L"Gun1.wav");
        if (bgSound != nullptr)
        {
            bgSound->PlayEffect();
        }
    }
    if (TEngine::gInput->GetKey(VK_RBUTTON) == KEY_PUSH)
    {
        if (m_pBGSound != nullptr)
        {
            m_pBGSound->Play();
        }
    }
    if (m_pBGSound && TEngine::gInput->GetKey('T') == KEY_PUSH)
    {
        m_pBGSound->PauseToggle();
    }
    if (m_pBGSound && TEngine::gInput->GetKey('S') == KEY_PUSH)
    {
        m_pBGSound->Stop();
    }
    if (m_pBGSound && TEngine::gInput->GetKey(VK_UP) == KEY_HOLD)
    {
        m_pBGSound->SetVolumeUp();
    }
    if (m_pBGSound && TEngine::gInput->GetKey(VK_DOWN) == KEY_HOLD)
    {
        m_pBGSound->SetVolumeDown();
    }

}
bool Sample::CreateFMOD()
{
    //Initialize 
    FMOD::System_Create(&TSound::m_pSystem);
    if (TSound::m_pSystem != nullptr)
    {
        TSound::m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
        return true;
    }      
    return false;
}
TSound* Sample::LoadSound(TString filepath)
{
	return Sample::g_SoundManager.LoadPtr(filepath);
}
bool Sample::CreateBlendState()
{
    D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
    bd.RenderTarget[0].BlendEnable = true;
    // RGB 혼합
	//RGB = SrcColor * SrcBlend OP DestColor * DestBlend;
    //RGB = SrcColor * D3D11_BLEND_SRC_ALPHA D3D11_BLEND_OP_ADD DestColor * D3D11_BLEND_INV_SRC_ALPHA;
    //RGB = SrcColor * arcalpha + DestColor * 1-arcalpha;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// alpha 혼합
    // A = SrcAlpha * 1 + DestAlpha * 0;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	// RGB 채널을 모두 사용
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_AlphaBlendState.GetAddressOf())))
    {
        return false;
    }
    // 가산블랜딩
    bd.RenderTarget[0].SrcBlend     = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend    = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOp  = D3D11_BLEND_OP_ADD;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_AddBlendState.GetAddressOf())))
    {
        return false;
    }
	// 뺄셈블랜딩( 소스-대상 )
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_SubtrackBlendState.GetAddressOf())))
    {
        return false;
    }
    // 뺄셈블랜딩( 대상-소스 )
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_RevSubtrackBlendState.GetAddressOf())))
    {
        return false;
    }
    // 곱셈블랜딩
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_MultiplyBlendState.GetAddressOf())))
    {
        return false;
    }
    // 듀얼소스컬러 블랜딩
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_SRC1_COLOR;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_DualSourceBlendState.GetAddressOf())))
    {
        return false;
    }
    return true;
}
LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
    TWindow::MsgProc(hWnd, message, wParam, lParam);
    return 1;
}
void Sample::GameRun()
{
    for (auto pNode = m_Engine.m_CompList.begin();pNode != m_Engine.m_CompList.end();pNode++)
    {
        (*pNode)->TickComponent();
    }
    if (GameLoop())
    {   
		TestFMOD(); // FMOD 테스트      

        m_MapObj->Tick();   
        m_TimerObj->Tick();
        m_EffectObj->Tick();
        m_Player->Tick();         
        m_World.Tick();
          
       m_dxDevice.PreRender();
            TDevice::m_pContext->OMSetBlendState(m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
            m_MapObj->Render();
            m_TimerObj->Render();
            TDevice::m_pContext->OMSetBlendState(m_DualSourceBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
            m_EffectObj->Render();
            TDevice::m_pContext->OMSetBlendState(m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
            m_Player->Render();
            m_World.Render();
        m_dxDevice.PostRender();
    }	
    if (m_pBGSound->m_pChannel == nullptr)
    {
        return;
    }

    if (m_pBGSound && m_pBGSound->IsPlaying())
    {
        m_pBGSound->m_pChannel->getPosition(&m_pBGSound->m_msPosition, FMOD_TIMEUNIT_MS);
        wchar_t buffer[256];
        swprintf(buffer, 256,
            L" 경과시간[%02d:%02d], 길이[%02d:%02d]",
            m_pBGSound->m_msPosition / 1000 / 60,
            m_pBGSound->m_msPosition / 1000 % 60,
            //m_msPosition / 10 % 60,
            m_pBGSound->m_msSoundLength / 1000 / 60, // 분
            m_pBGSound->m_msSoundLength / 1000 % 60);// 초
    }

    TSound::UpdateSystem(); // 사운드 업데이트
}
void Sample::InitGame()
{
   // 한글 출력
   std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    P(L"%s\n", L"Create DirectX  : true");
    m_dxDevice.CreateDevice(GetHwnd());
    m_dxDevice.CreateRenderTargetView();
    m_dxDevice.SetViewPort();    
    
    CreateFMOD();
	m_pBGSound = LoadSound(L"../../data/sound/00_Menu.mp3");
    auto effectsound = LoadSound(L"../../data/sound/Gun1.wav");
    auto bgSound = 
        Sample::g_SoundManager.GetAsset(L"00_Menu.mp3");
    if (bgSound != nullptr)
    {
        bgSound->Play(true);
    }

    if (CreateBlendState())
    {
		TDevice::m_pContext->OMSetBlendState(
            m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    }

    m_Engine.Init();
	m_World.Init();
   
    std::wstring name = L"Background";
    name += std::to_wstring(0);// 정수가 스크링이 된다.
    m_MapObj = std::make_shared<AActor>(name);
    if (m_MapObj->Create({ 0.0f, 0.0f }, { 800.0f,600.0f },
        L"../../data/texture/bg2.png",
        L"../../data/shader/DefaultShader.txt"))
    {       
    }    
   
	m_TimerObj = std::make_shared<ATimerEffect>(L"GameTimer");
    if (m_TimerObj->Create({ 700.0f, 0.0f }, { 50.0f,50.0f },
        L"../../data/ui/0.png",
        L"../../data/shader/DefaultShader.txt"))
    {       
        auto sprite = TEngine::gSpriteManager.GetAsset(L"DefalultNumber");
        m_TimerObj->SetSprite(sprite);
    }
    m_EffectObj = std::make_shared<AActor>(L"GameEffect");
    if (m_EffectObj->Create({ 0.0f, 0.0f }, { 100.0f,100.0f },
        L"../../data/effect/frgg.DDS",//get_item_03.dds",
        L"../../data/shader/DualSourceBlend.txt"))
    {
    }
        
    for (int i = 0; i < 10; i++)
    {
        TString name = L"NPC_A";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<ANpcCharacter>(name);       
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ x, y },{ 68.0f, 80.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 46.0f+1.0f, 62.0f + 1.0f };
            TVector2 s = { 68.0f-2.0f, 79.0f-2.0f };
            npc->UpdateUVVertexData(p, s);
            npc->UpdateVertexBuffer();
            m_World.m_ActorList.insert(std::make_pair(name, npc));
        }
    }   
    for (int i = 0; i < 10; i++)
    {
        TString name = L"NPC_B";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<ANpcCharacter>(name);
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ x, y }, { 44.0f, 77.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 1.0f + 1.0f, 62.0f + 1.0f };
            TVector2 s = { 44.0f - 2.0f, 76.0f - 2.0f };
            npc->UpdateUVVertexData(p, s);
            npc->UpdateVertexBuffer();
            m_World.m_ActorList.insert(std::make_pair(name, npc));
        }
    }
    for (int i = 0; i < 10; i++)
    {
        TString name = L"NPC_C";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<ANpcCharacter>(name);
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ x, y }, { 37.0f, 37.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 115.0f + 1.0f, 62.0f + 1.0f };
            TVector2 s = { 37.0f - 2.0f, 37.0f - 2.0f };
            npc->UpdateUVVertexData(p, s);
            npc->UpdateVertexBuffer();
            m_World.m_ActorList.insert(std::make_pair(name, npc));
        }
    }

    name.clear();
    name = L"Player";    
    m_Player = std::make_shared<APlayerCharacter>(name);
    m_Player->SetName(name);

    if (m_Player->Create({ 400.0f, 300.0f }, { 43.0f,62.0f },
        L"../../data/texture/bitmap1.bmp", 
        L"../../data/texture/bitmap2.bmp",
        L"../../data/shader/Player.txt"))
    {        
        TVector2 p = {91.0f, 2.0f};
        TVector2 s = {40.0f, 58.0f};
        m_Player->UpdateUVVertexData(p,s);
        m_Player->UpdateVertexBuffer();         
    }
    m_World.m_pPlayer = m_Player;

    std::wcout << UActorComponent::GetNumInstance() << std::endl;
  
    
}
bool Sample::GameLoop()
{   
    return true;
}
void Sample::ReleaseGame()
{
    P(L"\n%s", L"Release DirectX  : true");
    TEngine::gTexManager.Clear();
    TEngine::gShaderManager.Clear();
    TEngine::gSpriteManager.Clear();
    Sample::g_SoundManager.Clear();
    
    m_dxDevice.Release();
   
    m_Engine.m_CompList.clear();
    m_World.m_ActorList.clear();

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
