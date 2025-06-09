#include "UWorld.h"
#include "ATimerEffect.h"
#include "ANpcCharacter.h"
#include "APlayerCharacter.h"

std::vector<TTexture> UWorld::g_listA;
std::vector<TTexture> UWorld::g_listB;
std::shared_ptr<UTimerComponent>	 UWorld::m_Timer= nullptr;
std::shared_ptr<UInputComponent>	 UWorld::m_Input= nullptr;

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
	auto effect = std::make_shared<AEffect>();
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