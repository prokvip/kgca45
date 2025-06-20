#include "TLobbyScene.h"
#include "APlayerCharacter.h"
#include "ANpcCharacter.h"
#include "TAssetManager.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
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
}
void TLobbyScene::Frame()
{
    m_MapObj->Tick();
}
void TLobbyScene::Render()
{
    TDevice::m_pContext->OMSetBlendState(TEngine::m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
    m_MapObj->Render();

}
void TLobbyScene::ReleaseScene()
{
    P(L"\n%s", L"TIntroScene::ReleaseGame  : true");
}