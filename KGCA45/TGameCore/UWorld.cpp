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
	TRect rtCollision;
	for (auto pro : m_Projectile)
	{
		pro->m_fLifeTimer -= g_fSPF;
		if (pro->m_fLifeTimer < 0.0f)
		{
			pro->m_bDraw = false;
			continue;
		}
		TVector2 pos = pro->GetPosition();
		pro->m_vDirection = { 0.0f,-1.0f };
		pos = pos + pro->m_vDirection * 500.0f * g_fSPF;
		//pro->m_fElapseTimer += g_fSPF;
		//pro->m_vDirection = { 0.0f, -1.0f };
	   // pos = m_pPlayer->GetPosition() + pro->m_vDirection * 100.0f * pro->m_fElapseTimer;
		//pos.x = m_pPlayer->GetPosition().x;

		pro->SetPosition(pos);
		pro->Tick();
	}

	for (auto& npc : m_ActorList)
	{
		if (npc.second->m_bDraw == false)
		{
			continue;
		}
		npc.second->Tick();
		// 발사체 충돌처리
		for (auto pro : m_Projectile)
		{		
			auto pos = npc.second->GetPosition();
			auto rt = npc.second->GetRect();
			if (rtCollision.IntersectRegion(rt, pro->GetRect()))
			{
				if (npc.second->m_bDraw == true)
				{
					m_iNumMissionClear--;
				}
				npc.second->m_bDraw = false;
				pro->m_bDraw = false;
				AddEffect(rtCollision.GetCenter());
			}
		}
		// 플레이어 충돌처리
		auto pos = npc.second->GetPosition();
		auto rt = npc.second->GetRect();
		if (rtCollision.IntersectRegion(rt, m_pPlayer->GetRect()))
		{
			npc.second->m_bDraw = false;
			m_pPlayer->m_bDraw = false;
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

	for (auto& pro : m_Projectile)
	{
		pro->Render();
	}

	// 발사체 리스트 소멸.
	for (auto iter = m_Projectile.begin();
		iter != m_Projectile.end(); )
	{
		AActor* pActor = iter->get();
		if (pActor->m_bDraw == false)
		{
			iter = m_Projectile.erase(iter);
		}
		else
		{
			iter++;
		}
	}
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