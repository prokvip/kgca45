#include "UWorld.h"
#include "ANpcCharacter.h"
#include "APlayerCharacter.h"
#include "TSprite.h"
#include <tchar.h>

void	UWorld::Init()
{	
	for (auto& data : TEngine::gSpriteManager.m_AssetMap)
	{
		auto sprite = data.second.get();	
		if(sprite->m_texlist.size())
			m_EffectListTex.emplace_back(sprite);
		else
			m_EffectListUV.emplace_back(sprite);
	}
}
void UWorld::Tick()
{
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
			AddEffectUV(rtCollision.GetCenter());
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
	sprite->m_pInitSize = { 50.0f,50.0f };
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
	sprite->m_pInitSize = { 50.0f,50.0f };
	sprite->m_fStep = 0.1f;	
	m_EffectList.emplace_back(sprite);
}
void   UWorld::Render()
{
	for (auto effect : m_EffectList)
	{
		if (effect->m_bDraw == false)
		{
			continue;
		}
		effect->Render();
	}
}