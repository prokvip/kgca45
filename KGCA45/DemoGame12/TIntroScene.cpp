#include "TIntroScene.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"

#include "TIntroScene.h"
#include "TLobbyScene.h"
#include "TGameScene.h"
#include "TResultScene.h"
#include "TFsm.h"


void TIntroScene::Process(APawn* pPlayer)
{
    m_Timer += g_fSPF;
    if (TEngine::gInput->GetKey(VK_RETURN) == KEY_PUSH)
    {
        m_Timer = 0.0f;
        SceneChange(TSCENE_STATE_INTRO, TSCENE_EVENT_ENTER);
    }
    if (m_Timer > 5.0f)
    {
        m_Timer = 0.0f;
        SceneChange(TSCENE_STATE_INTRO, TSCENE_EVENT_TIMEOUT);
    }
}

void TIntroScene::InitScene()
{
    P(L"\n%s", L"TIntroScene::InitScene()  : true");
    auto BackgroundSound = TEngine::gSoundManager.LoadPtr(L"../../data/sound/00_Menu.mp3");
    auto EffectSound = TEngine::gSoundManager.LoadPtr(L"../../data/sound/Gun1.wav");

    m_Soundlist.emplace_back(BackgroundSound);
    m_Soundlist.emplace_back(EffectSound);

    auto bgSound = TEngine::gSoundManager.GetAsset(L"00_Menu.mp3");
    if (bgSound != nullptr)
    {
        bgSound->Play(true);
    }   

    std::wstring name = L"Background";
    name += std::to_wstring(0);// 정수가 스크링이 된다.
    m_MapObj = std::make_shared<AActor>(name);
    if (m_MapObj->Create({ 0.0f, 0.0f }, { 800.0f,600.0f },
        L"../../data/texture/introbg.png",
        L"../../data/shader/DefaultShader.txt"))
    {
    }    
}
void TIntroScene::Tick()
{
    //TVector2 cam = { 400.0f, 300.0f };
    //cam.x += cosf(g_fGameTimer) * 400.0f;
   
    TVector2 cam = UWorld::m_vCameraPos;
    cam.x += g_fSPF * 50.0f;
    if (TEngine::gInput->GetKey('D') == KEY_HOLD)
    {
        cam.x += g_fSPF * 100.0f;
    }
    if (TEngine::gInput->GetKey('A') == KEY_HOLD)
    {
        cam.x -= g_fSPF * 100.0f;
    }
    if (TEngine::gInput->GetKey('W') == KEY_HOLD)
    {
        cam.y -= g_fSPF * 100.0f;
    }
    if (TEngine::gInput->GetKey('S') == KEY_HOLD)
    {
        cam.y += g_fSPF * 100.0f;
    }
    m_World->m_vCameraPos = cam;
    m_MapObj->Tick();
}
void TIntroScene::Render()
{
    TDevice::m_pContext->OMSetBlendState(TEngine::m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    m_MapObj->Render();   
     
}
void TIntroScene::ReleaseScene()
{
    P(L"\n%s", L"TIntroScene::ReleaseGame  : true");
}