#include "TLobbyScene.h"
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

void   TButton::Tick()
{
    auto mouse = TEngine::gInput->GetPos();

    if (GetRect().IsPointInRegion(mouse.x, mouse.y))
    {
        m_iCurrentIndex = T_STATE_MOUSEOVER;
        if (TEngine::gInput->GetKey(VK_LBUTTON) == KEY_PUSH ||
            TEngine::gInput->GetKey(VK_LBUTTON) == KEY_HOLD)
        {
            m_iCurrentIndex = T_STATE_PRESSED;
        }
        if (TEngine::gInput->GetKey(VK_LBUTTON) == KEY_UP)
        {
            m_iCurrentIndex = T_STATE_SELECT;
        } 
    }
    else
    {
        m_iCurrentIndex = 0;
    }

}
void TLobbyScene::Process(APawn* pPlayer)
{
    m_Timer += g_fSPF;
    // 1번 이벤트 엔터키
    //if (TEngine::gInput->GetKey(VK_RETURN) == KEY_PUSH)
    if(m_StartBtn->m_iCurrentIndex == T_STATE_SELECT)
    {
        m_pOwner->m_pInGameScene->ReleaseScene();
        m_pOwner->m_pInGameScene.reset(new TGameScene(m_pOwner));
        m_pOwner->m_pInGameScene->InitScene();
        m_pOwner->m_SceneList[TSCENE_STATE_INGAME] =
            m_pOwner->m_pInGameScene;
        SceneChange(TSCENE_STATE_LOBBY, TSCENE_EVENT_START);
    }
}
void TLobbyScene::InitScene()
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
        L"../../data/texture/lobbybg.png",
        L"../../data/shader/DefaultShader.txt"))
    {
    }

    

    std::wstring namebtn = L"StartBtn";
    namebtn += std::to_wstring(0);// 정수가 스크링이 된다.
    m_StartBtn = std::make_shared<TButton>(namebtn);
    auto pos = TVector2(400.0f - 334.0f * 0.5f, 300.0f - 41.0f);
    if (m_StartBtn->Create(pos, { 334.0f,82.0f },
        L"../../data/ui/main_start_nor.png",
        L"../../data/shader/DefaultShader.txt"))
    {
        auto effect = TEngine::gSpriteManager.GetAsset(L"startbtn");
        m_StartBtn->m_pEffect = effect;
        m_StartBtn->m_pInitPos = pos;
        m_StartBtn->m_pInitSize = m_StartBtn->GetRect().GetSize();
    }

    UWorld::m_vCameraPos = { 400.0f, 300.0f };
}
void TLobbyScene::Tick()
{
    m_MapObj->Tick();
    m_StartBtn->Tick();
}
void TLobbyScene::Render()
{
    TDevice::m_pContext->OMSetBlendState(TEngine::m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    m_MapObj->Render();
    m_StartBtn->Render();

}
void TLobbyScene::ReleaseScene()
{
    P(L"\n%s", L"TIntroScene::ReleaseGame  : true");
}