#include "TGameScene.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"

#include "TIntroScene.h"
#include "TLobbyScene.h"
#include "TGameScene.h"
#include "TResultScene.h"

#include "TSceneFSM.h"
void TGameScene::Process(UPawn* pPlayer)
{
    m_Timer += g_fSPF;
    // 1번 이벤트 엔터키
    if (TEngine::gInput->GetKey(VK_RETURN) == KEY_PUSH)
    {
        //m_pOwner->m_pInGameScene->ReleaseScene();
        //m_pOwner->m_pInGameScene.reset(new TGameScene(m_pOwner));
        //m_pOwner->m_pInGameScene->InitScene();
        int iOutput = IScene.GetTransition(
            TSCENE_STATE_INGAME,
            ESceneEvent::TSCENE_EVENT_ENTER);
        m_pOwner->m_pCurrentScene = m_pOwner->m_SceneList[iOutput].get();
    }
    // 2번 아무키나 누르면 게임 시작
    if (m_Timer > 10.0f)
    {
        m_Timer = 0.0f;
        int iOutput = IScene.GetTransition(
            TSCENE_STATE_INGAME,
            ESceneEvent::TSCENE_EVENT_TIMEOUT);
        m_pOwner->m_pCurrentScene = m_pOwner->m_SceneList[iOutput].get();
    }
}

void TGameScene::InitScene()
{
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
    if (m_TimerObj->Create({ 700.0f, 0.0f }, { 50.0f,50.0f },
        L"../../data/ui/0.png",
        L"../../data/shader/DefaultShader.txt"))
    {
        auto sprite = TEngine::gSpriteManager.GetAsset(L"DefalultNumber");
        m_TimerObj->SetSprite(sprite);
    }

    m_EffectObj = std::make_shared<AActor>(L"GameEffect");
    if (m_EffectObj->Create({ 0.0f, 0.0f }, { 800.0f,600.0f },
        L"../../data/texture/frgg.DDS",//get_item_03.dds",
        L"../../data/shader/DualSourceBlend.txt"))
    {
    }

    for (int i = 0; i < 1; i++)
    {
        TString name = L"NPC_A";
        name += std::to_wstring(i);// 정수가 스크링이 된다.
        auto npc = std::make_shared<ANpcCharacter>(name);
        float x = randstep(0.0f, 800.0f);
        float y = randstep(0.0f, 600.0f);
        npc->m_vDirection.x = randstep(-1.0f, +1.0f);
        npc->m_vDirection.y = randstep(-1.0f, +1.0f);
        if (npc->Create({ x, y }, { 68.0f, 80.0f },
            L"../../data/texture/bitmap1.bmp",
            L"../../data/texture/bitmap2.bmp",
            L"../../data/shader/Player.txt"))
        {
            TVector2 p = { 46.0f + 1.0f, 62.0f + 1.0f };
            TVector2 s = { 68.0f - 2.0f, 79.0f - 2.0f };
            npc->UpdateUVVertexData(p, s);
            npc->UpdateVertexBuffer();
            m_World->m_ActorList.insert(std::make_pair(name, npc));
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
            m_World->m_ActorList.insert(std::make_pair(name, npc));
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
            m_World->m_ActorList.insert(std::make_pair(name, npc));
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
        TVector2 p = { 91.0f, 2.0f };
        TVector2 s = { 40.0f, 58.0f };
        m_Player->UpdateUVVertexData(p, s);
        m_Player->UpdateVertexBuffer();
    }
    m_World->m_pPlayer = m_Player;
}
void TGameScene::Frame()
{
    TestFMOD(); // FMOD 테스트      

    m_MapObj->Tick();
    m_EffectObj->Tick();
     //m_TimerObj->Tick();
   m_EffectObj->Tick();
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
    //m_TimerObj->Render();
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