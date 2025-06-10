#include "UWorld.h"
#include "ANpcCharacter.h"
#include "APlayerCharacter.h"
#include "ATimerEffect.h"
#include <tchar.h>

void	UWorld::Init()
{	
	for (auto& data : TEngine::gSpriteManager.m_AssetMap)
	{
		auto sprite = data.second.get();	
		if(sprite->m_texlist.size())
			effectListTex.emplace_back(sprite);
		else
			effectListUV.emplace_back(sprite);
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
			AddEffectTex(rtCollision.GetPos());			
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
	if (m_iCurrentIndex >= effectListTex.size())
	{
		m_iCurrentIndex = 0;
	}	
	auto sprite = std::make_shared<TEffect>();
	//auto sprite = TEngine::gSpriteManager.GetAsset(L"lot_wik");
	sprite->m_pEffect = effectListTex[m_iCurrentIndex++];
	sprite->m_pInitPos = pos;
	sprite->m_pInitSize = { 50.0f,50.0f };
	sprite->m_fStep = 0.1f;
	if (m_iCurrentIndex == 1)
	{
		sprite->m_fStep = 1.0f;
	}
	m_EffectList.emplace_back(sprite);
	

	/*std::wstring name = L"effect";
	name += std::to_wstring(m_ActorList.size());
	auto effect = std::make_shared<AEffectTex>();
	if (effect->Create(pos, { 50.0f,50.0f },
		L"../../data/texture/get_item_03.dds",
		L"../../data/shader/DefaultShader.txt"))
	{
		effect->m_fStep = 0.1f;
		effect->SetTextureList(UWorld::g_listB);
		m_EffectList.emplace_back(effect);
	}*/
}
void   UWorld::AddEffectUV(TVector2 pos)
{
	/*std::wstring name = L"effect";
	name += std::to_wstring(m_ActorList.size());
	auto effect = std::make_shared<AEffectUV>();
	if (effect->Create(pos, { 50.0f,50.0f },
		L"../../data/texture/get_item_03.dds",
		L"../../data/shader/DefaultShader.txt"))
	{
		effect->m_fStep = 0.1f;
		effect->SetTextureList(UWorld::g_listB);
		m_EffectList.emplace_back(effect);
	}*/
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