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
#include "TSceneFSM.h"


void TIntroScene::Process(UPawn* pPlayer)
{
    m_Timer += g_fSPF;
    // 1번 이벤트 엔터키
    if (TEngine::gInput->GetKey(VK_RETURN) == KEY_PUSH)
    {
        /*m_pLobbyScene->ReleaseScene();
        m_pLobbyScene.reset(new TLobbyScene());
        m_pLobbyScene->InitScene();*/
        int iOutput = IScene.GetTransition(
            TSCENE_STATE_INTRO,
            ESceneEvent::TSCENE_EVENT_ENTER);
        m_pOwner->m_pCurrentScene = m_pOwner->m_SceneList[iOutput].get();
            //m_pOwner->m_pLobbyScene.get();
    }
	// 2번 아무키나 누르면 게임 시작
    if (m_Timer > 5.0f)
    {
        m_Timer = 0.0f;
        int iOutput = IScene.GetTransition(
            TSCENE_STATE_INTRO,
            ESceneEvent::TSCENE_EVENT_TIMEOUT);
        m_pOwner->m_pCurrentScene = m_pOwner->m_SceneList[iOutput].get();

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
void TIntroScene::Frame()
{
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