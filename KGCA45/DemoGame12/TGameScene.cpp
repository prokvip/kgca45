#include "TGameScene.h"
#include "APlayerCharacter.h"
#include "ANpc.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"

#include "TIntroScene.h"
#include "TLobbyScene.h"
#include "TGameScene.h"
#include "TResultScene.h"

#include "TFsm.h"

int  TGameScene::g_iNumNpc=1;

void TGameScene::Process(APawn* pPlayer)
{
    m_Timer += g_fSPF;
    m_NpcKillObj->m_iSecond = m_World->m_iNumMissionClear;
    if(m_World->m_iNumMissionClear==0)
    //if (TEngine::gInput->GetKey(VK_RETURN) == KEY_PUSH)
    {
        int iOutput = m_pOwner->m_pFsm.GetTransition(
            TSCENE_STATE_INGAME,
            TSCENE_EVENT_ENTER);
        g_iNumNpc++;
        m_pOwner->m_pCurrentScene = m_pOwner->m_SceneList[iOutput].get();
    }
    // 2번 아무키나 누르면 게임 시작
    if (m_Player.get()->m_bDraw == false)
    {
        m_Timer = 0.0f;
        int iOutput = m_pOwner->m_pFsm.GetTransition(
            TSCENE_STATE_INGAME,
            TSCENE_EVENT_END);
        Sleep(1000);        
        m_pOwner->m_pCurrentScene = m_pOwner->m_SceneList[iOutput].get();
    }
}

void TGameScene::InitScene()
{
    m_NpcManager.Init();

    m_pBGSound = TEngine::gSoundManager.LoadPtr(L"../../data/sound/abel_leaf.asf");
    auto effectsound = TEngine::gSoundManager.LoadPtr(L"../../data/sound/Gun1.wav");
    auto bgSound = TEngine::gSoundManager.GetAsset(L"abel_leaf.asf");
    m_Soundlist.emplace_back(m_pBGSound);
    m_Soundlist.emplace_back(effectsound);
    if (bgSound != nullptr)
    {
        bgSound->Play(true);
    }

    m_World = std::make_shared<UWorld>();

    std::wstring name = L"Background";
    name += std::to_wstring(0);// 정수가 스크링이 된다.
    m_MapObj = std::make_shared<AActor>(name);
    if (m_MapObj->Create({ 0.0f, 0.0f }, { 800.0f,600.0f },
        L"../../data/texture/bg2.png",
        L"../../data/shader/DefaultShader.txt"))
    {
    }

    m_TimerObj = std::make_shared<ATimerEffect>(L"GameTimer");
    if (m_TimerObj->Create({ 370.0f, 0.0f }, { 50.0f,50.0f },
        L"../../data/ui/0.png",
        L"../../data/shader/DefaultShader.txt"))
    {
        auto sprite = TEngine::gSpriteManager.GetAsset(L"DefalultNumber");
        m_TimerObj->SetSprite(sprite);
    }
    m_NpcKillObj = std::make_shared<ATimerEffect>(L"NpcKill");
    if (m_NpcKillObj->Create({ 700.0f, 0.0f }, { 50.0f,50.0f },
        L"../../data/ui/0.png",
        L"../../data/shader/DefaultShader.txt"))
    {
        auto sprite = TEngine::gSpriteManager.GetAsset(L"DefalultNumber");
        m_NpcKillObj->SetSprite(sprite);
    }

    m_EffectObj = std::make_shared<AActor>(L"GameEffect");
    if (m_EffectObj->Create({ 0.0f, 0.0f }, { 100.0f,100.0f },
        L"../../data/effect/frgg.DDS",//get_item_03.dds",
        L"../../data/shader/DualSourceBlend.txt"))
    {
    }

    for (int i = 0; i < g_iNumNpc; i++)
    {
        TString name = L"NPC_A";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<ANpc>(name);    
        npc->m_pMgr = &m_NpcManager;
        npc->m_iPatternType = 0;
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ 400.0f, 40.0f }, { 68.0f, 80.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 46.0f + 1.0f, 62.0f + 1.0f };
            TVector2 s = { 68.0f - 2.0f, 79.0f - 2.0f };
            npc->UpdateUVVertexData(p, s);
            m_World->m_ActorList.insert(std::make_pair(name, npc));
        }
    }
    for (int i = 0; i < g_iNumNpc; i++)
    {
        TString name = L"NPC_B";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<ANpc>(name);
        npc->m_pMgr = &m_NpcManager;
        npc->m_iPatternType = 1;
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ x, 40 }, { 44.0f, 77.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 1.0f + 1.0f, 62.0f + 1.0f };
            TVector2 s = { 44.0f - 2.0f, 76.0f - 2.0f };
            npc->UpdateUVVertexData(p, s);
            m_World->m_ActorList.insert(std::make_pair(name, npc));
        }
    }
    for (int i = 0; i < g_iNumNpc; i++)
    {
        TString name = L"NPC_C";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<ANpc>(name);
        npc->m_pMgr = &m_NpcManager;
        npc->m_iPatternType = 2;
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ x, 40 }, { 37.0f, 37.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 115.0f + 1.0f, 62.0f + 1.0f };
            TVector2 s = { 37.0f - 2.0f, 37.0f - 2.0f };
            npc->UpdateUVVertexData(p, s);
            m_World->m_ActorList.insert(std::make_pair(name, npc));
        }
    }
    m_World->m_iNumMissionClear = m_World->m_ActorList.size();

    name.clear();
    name = L"Player";
    m_Player = std::make_shared<APlayerCharacter>(name);
    m_Player->SetName(name);

    if (m_Player->Create({ 400.0f, 300.0f }, { 43.0f,62.0f },
        L"../../data/texture/bitmap1.bmp",
        L"../../data/texture/bitmap2.bmp",
        L"../../data/shader/Player.txt"))
    {
        TVector2 p = { 91.0f, 2.0f };
        TVector2 s = { 40.0f, 58.0f };
        m_Player->UpdateUVVertexData(p, s);
    }
    m_World->m_pPlayer = m_Player;
}

void TGameScene::Tick()
{
    //TestFMOD(); // FMOD 테스트      
    if (TEngine::gInput->GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        auto bgSound = TEngine::gSoundManager.GetAsset(L"Gun1.wav");
        if (bgSound != nullptr)
        {
            bgSound->PlayEffect();
        }
        auto left = std::make_shared<AActor>(L"");
        auto start = m_Player->GetPosition();        
        auto end = start + TVector2(m_Player->GetRect().GetSize().x- 8.0f, 0);
        if (left->Create(start, {8.0f,22.0f},
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 276.0f, 2.0f };
            TVector2 s = { 8.0f, 22.0f };
            left->UpdateUVVertexData(p, s);
            left->m_fLifeTimer = 3.0f;
        }
        m_World->m_Projectile.push_back(left);

        auto right = std::make_shared<AActor>(L"");
        if (right->Create(end, { 8.0f,22.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 276.0f, 2.0f };
            TVector2 s = { 8.0f, 22.0f };
            right->UpdateUVVertexData(p, s);
            right->m_fLifeTimer = 3.0f;
        }
        m_World->m_Projectile.push_back(right);
    }
    
    m_MapObj->Tick();
    m_EffectObj->Tick();
    m_TimerObj->Tick();
    m_NpcKillObj->Tick();
    m_Player->Tick();
    m_World->Tick();
    
    for (auto sound : m_Soundlist)
    {
        if (sound->IsPlaying())
        {
            sound->Update();
        }
    }
}
void TGameScene::Render()
{
    TDevice::m_pContext->OMSetBlendState(TEngine::m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    m_MapObj->Render();
    m_TimerObj->Render();
    m_NpcKillObj->Render();

    TDevice::m_pContext->OMSetBlendState(TEngine::m_DualSourceBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    m_EffectObj->Render();    

    TDevice::m_pContext->OMSetBlendState(TEngine::m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    m_Player->Render();    
   
    m_World->Render();
}
void TGameScene::ReleaseScene()
{
    P(L"\n%s", L"Scene::ReleaseGame  : true");
    m_Soundlist.clear();
}
void TGameScene::TestFMOD()
{
    /// 사운드 테스트
    if (TEngine::gInput->GetKey(VK_LBUTTON) == KEY_PUSH)
    {
        auto bgSound =
            TEngine::gSoundManager.GetAsset(L"Gun1.wav");
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