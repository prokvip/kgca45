#include "Sample.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"

bool Sample::CreateBlendState()
{
    D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
    bd.RenderTarget[0].BlendEnable = true;
    // RGB ȥ��
	//RGB = SrcColor * SrcBlend OP DestColor * DestBlend;
    //RGB = SrcColor * D3D11_BLEND_SRC_ALPHA D3D11_BLEND_OP_ADD DestColor * D3D11_BLEND_INV_SRC_ALPHA;
    //RGB = SrcColor * arcalpha + DestColor * 1-arcalpha;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// alpha ȥ��
    // A = SrcAlpha * 1 + DestAlpha * 0;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	// RGB ä���� ��� ���
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_AlphaBlendState.GetAddressOf())))
    {
        return false;
    }
    // �������
    bd.RenderTarget[0].SrcBlend     = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend    = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOp  = D3D11_BLEND_OP_ADD;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_AddBlendState.GetAddressOf())))
    {
        return false;
    }
	// ��������( �ҽ�-��� )
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_SubtrackBlendState.GetAddressOf())))
    {
        return false;
    }
    // ��������( ���-�ҽ� )
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_RevSubtrackBlendState.GetAddressOf())))
    {
        return false;
    }
    // ��������
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    if (FAILED(TDevice::m_pd3dDevice->CreateBlendState(&bd, m_MultiplyBlendState.GetAddressOf())))
    {
        return false;
    }
    // ���ҽ��÷� ����
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
        m_MapObj->Tick();   
        m_TimerObj->Tick();
        m_EffectObj->Tick();
        m_Player->Tick();
        for (auto& p : m_World.m_ActorList)
        {
            if (p.second->m_bDraw == false)
            {
                continue;
            }
            p.second->Tick();
        }
           
        m_World.Tick();
          
       m_dxDevice.PreRender();
            TDevice::m_pContext->OMSetBlendState(m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
            m_MapObj->Render();
            m_TimerObj->Render();
            TDevice::m_pContext->OMSetBlendState(m_DualSourceBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
            m_EffectObj->Render();

            TDevice::m_pContext->OMSetBlendState(m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);

            m_Player->Render();
            for (auto& p : m_World.m_ActorList)
            {
                if (p.second->m_bDraw == false)
                {
                    continue;
                }
                p.second->Render();
            }
            m_World.Render();
        m_dxDevice.PostRender();
    }	
}
void Sample::InitGame()
{
   // �ѱ� ���
   std::wcout.imbue(std::locale("kor"));//setlocale(LC_ALL, "korean");

    P(L"%s\n", L"Create DirectX  : true");
    m_dxDevice.CreateDevice(GetHwnd());
    m_dxDevice.CreateRenderTargetView();
    m_dxDevice.SetViewPort();    

    if (CreateBlendState())
    {
		TDevice::m_pContext->OMSetBlendState(
            m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    }

    m_Engine.Init();
	m_World.Init();
   
    std::wstring name = L"Background";
    name += std::to_wstring(0);// ������ ��ũ���� �ȴ�.
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
        m_TimerObj->SetTextureList(sprite->m_texlist);
    }
    m_EffectObj = std::make_shared<AActor>(L"GameEffect");
    if (m_EffectObj->Create({ 0.0f, 0.0f }, { 800.0f,600.0f },
        L"../../data/texture/frgg.DDS",//get_item_03.dds",
        L"../../data/shader/DualSourceBlend.txt"))
    {
    }
        
    for (int i = 0; i < 10; i++)
    {
        TString name = L"NPC_A";
        name += std::to_wstring(i);// ������ ��ũ���� �ȴ�.
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
        name += std::to_wstring(i);// ������ ��ũ���� �ȴ�.
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
        name += std::to_wstring(i);// ������ ��ũ���� �ȴ�.
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
    m_dxDevice.Release();

    std::wcout << std::endl;
    std::wcout << TEngine::gTimer->GetGameGlobalTimer() << std::endl;

    m_Engine.m_CompList.clear();
    m_World.m_ActorList.clear();

    std::wcout << L"���� �ν��Ͻ� ���� : " << UActorComponent::GetNumInstance() << std::endl;
}

int main()
{
    Sample game;
    game.SetWindow(GetModuleHandle(nullptr));
    game.InitGame();
    game.Run();
    game.ReleaseGame();
    _getch();
}
