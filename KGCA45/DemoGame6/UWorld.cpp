#include "UWorld.h"
#include "ATimerEffect.h"
#include "ANpcCharacter.h"
#include "APlayerCharacter.h"
#include <tchar.h>

std::vector<TTexture> UWorld::g_listA;
std::vector<TTexture> UWorld::g_listB;
std::shared_ptr<UTimerComponent>	 UWorld::m_Timer= nullptr;
std::shared_ptr<UInputComponent>	 UWorld::m_Input= nullptr;
std::vector<TSprite>  UWorld::g_Sprite;

bool    UWorld::GameDataLoad(TString path)
{ 
	TCHAR pBuffer[256] = { 0 };
	TCHAR pTemp[256] = { 0 };
	TCHAR pTexturePath[256] = { 0 };
	TCHAR pMaskTexturePath[256] = { 0 };
	TCHAR pShaderPath[256] = { 0 };
	int iIsTexAnimation = 0;
	int iNumSprite = 0;

	FILE* fp_src;
	_wfopen_s(&fp_src, path.c_str(), L"rt");
	if (fp_src == NULL) return false;

	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, _T("%s"), pTemp, (unsigned int)_countof(pTemp));
	for (;;)
	{
			
		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d%d %s%s%s"),
			pTemp, (unsigned int)_countof(pTemp), &iNumFrame,
			&iIsTexAnimation,  // UV_Animation=0, TEX_CHANGE_Animation
			pTexturePath, (unsigned int)_countof(pTexturePath),
			pMaskTexturePath, (unsigned int)_countof(pMaskTexturePath),
			pShaderPath, (unsigned int)_countof(pShaderPath));

		TSprite sprite;
		sprite.m_Name				= pTemp;
		sprite.m_iNumFrame			= iNumFrame;
		sprite.m_iType				= iIsTexAnimation;
		sprite.m_szTextureFilePath	= pTexturePath;
		sprite.m_szMaskTextureFilePath = pMaskTexturePath;		
		sprite.m_szShaderFilePath	= pShaderPath;

		int iReadFrame = 0;
		if (iIsTexAnimation == TSprite::TEX_Animation) 
		{
			sprite.m_texArray.resize(iNumFrame);
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp_src);
				_stscanf_s(pBuffer, _T("%d %s"),
					&iReadFrame,
					pTexturePath, (unsigned int)_countof(pTexturePath));
				sprite.m_texArray[iFrame] = pTexturePath;
			}
		}
		else //TSprite::UV_Animation
		{
			sprite.m_uvArray.resize(iNumFrame);
			for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp_src);
				_stscanf_s(pBuffer, _T("%d %d %d %d %d"),
					&iReadFrame,
					&sprite.m_uvArray[iFrame].left, &sprite.m_uvArray[iFrame].top,
					&sprite.m_uvArray[iFrame].right, &sprite.m_uvArray[iFrame].bottom);
			}	
		}

		TString name = pTemp;
		if (name == L"#END")
		{
			break;
		}

		g_Sprite.emplace_back(sprite);
	}
	fclose(fp_src);
	return true;
}
void	UWorld::Init()
{
	GameDataLoad(L"../../data/script/SpriteInfo.txt");
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