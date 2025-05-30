#include "UWorld.h"
#include "TTimerEffect.h"

std::vector<TTexture> UWorld::g_listA;
std::vector<TTexture> UWorld::g_listB;

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
			AddEffect(rtCollision.GetPos());			
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
	std::wstring name = L"effect";
	name += std::to_wstring(m_ActorList.size());
	auto effect = std::make_shared<TEffect>();
	if (effect->Create(pos, { 50.0f,50.0f },
		L"../../data/texture/get_item_03.dds",
		L"../../data/shader/DefaultShader.txt"))
	{
		effect->m_fStep = 0.1f;
		effect->SetTextureList(UWorld::g_listB);
		m_EffectList.emplace_back(effect);
	}
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