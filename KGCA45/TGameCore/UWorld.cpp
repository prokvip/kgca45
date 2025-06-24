#include "UWorld.h"
#include "ANpcCharacter.h"
#include "APlayerCharacter.h"
#include "TSprite.h"
#include <tchar.h>
std::shared_ptr<APlayerCharacter> UWorld::m_pPlayer = nullptr;
void	UWorld::Init()
{	
	for (auto& data : TEngine::gSpriteManager.m_AssetMap)
	{
		auto sprite = data.second.get();	
		if(sprite->m_texlist.size())
			m_EffectListTex.emplace_back(sprite);
		else
			m_EffectListUV.emplace_back(sprite);

		m_Effects.emplace_back(sprite);
	}
}
void	UWorld::Tick()
{
	for (auto& p : m_ActorList)
	{
		if (p.second->m_bDraw == false)
		{
			continue;
		}
		p.second->Tick();
	}
	TRect rtCollision;
	for( auto npc : m_ActorList)
	{
		if (npc.second->m_bDraw == false)
		{
			continue;
		}
		auto pos = npc.second->GetPosition();
		auto rt = npc.second->GetRect();
		if (rtCollision.IntersectRegion(rt, m_pPlayer->GetRect()))
		{
			npc.second->m_bDraw = false;
			//AddEffectTex(rtCollision.GetCenter());			
			//AddEffectUV(rtCollision.GetCenter());
			AddEffect(rtCollision.GetCenter());			
		}
	}
	for (auto effect : m_EffectList)
	{
		if (effect->m_bDraw == false)
		{
			continue;
		}
		effect->Tick();
	}
	
}
void   UWorld::AddEffect(TVector2 pos)
{
	auto sprite = std::make_shared<TEffect>();
	if(rand() % 2 == 0)
	{
		auto effect = TEngine::gSpriteManager.GetAsset(L"lot_wik");
		sprite->m_pEffect = effect;
	}
	else
	{
		auto effect = TEngine::gSpriteManager.GetAsset(L"firewall");
		sprite->m_pEffect = effect;
	}
	sprite->m_szName = sprite->m_pEffect->GetName();
	sprite->m_pInitPos = pos;
	sprite->m_pInitSize = sprite->m_pEffect->m_pInitSize;
	sprite->m_fStep = 0.1f;	
	m_EffectList.emplace_back(sprite);
}
void   UWorld::AddEffectTex(TVector2 pos)
{
	if (m_iCurrentIndex >= m_EffectListTex.size())
	{
		m_iCurrentIndex = 0;
	}	
	auto sprite = std::make_shared<TEffect>();
	//auto sprite = TEngine::gSpriteManager.GetAsset(L"lot_wik");
	sprite->m_pEffect = m_EffectListTex[m_iCurrentIndex++];	
	sprite->m_szName = sprite->m_pEffect->GetName();
	sprite->m_pInitPos = pos;
	sprite->m_pInitSize = sprite->m_pEffect->m_pInitSize;
	sprite->m_fStep = 0.1f;
	if (m_iCurrentIndex == 1)
	{
		sprite->m_fStep = 1.0f;
	}
	m_EffectList.emplace_back(sprite);
}
void   UWorld::AddEffectUV(TVector2 pos)
{
	if (m_iCurrentIndex >= m_EffectListUV.size())
	{
		m_iCurrentIndex = 0;
	}
	auto sprite = std::make_shared<TEffect>();
	
	//auto sprite = TEngine::gSpriteManager.GetAsset(L"lot_wik");
	sprite->m_pEffect = m_EffectListUV[m_iCurrentIndex++];		
	sprite->m_szName = sprite->m_pEffect->GetName();
	sprite->m_pInitPos = pos;
	sprite->m_pInitSize = sprite->m_pEffect->m_pInitSize;
	sprite->m_fStep = 0.1f;	
	m_EffectList.emplace_back(sprite);
}
void   UWorld::Render()
{
	TDevice::m_pContext->OMSetBlendState(TEngine::m_DualSourceBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);
	for (auto effect : m_EffectList)
	{
		if (effect->m_bDraw == false)
		{
			continue;
		}
		effect->Render();
	}
	TDevice::m_pContext->OMSetBlendState(TEngine::m_AlphaBlendState.Get(), nullptr, -1);// 0xFFFFFFFF);

	for (auto& p : m_ActorList)
	{
		if (p.second->m_bDraw == false)
		{
			continue;
		}
		p.second->Render();
	}
	/*auto effect = m_EffectList.back();
	m_EffectList.pop_back();
	m_EffectList[0] = effect;
	m_iNumEffect--;*/
}
void   UWorld::Release()
{
	m_ActorList.clear();
	m_EffectList.clear();
	m_EffectListTex.clear();
	m_EffectListUV.clear();
	m_Effects.clear();
}
UWorld::~UWorld()
{	
	Release();
}