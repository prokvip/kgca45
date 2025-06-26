#pragma once
#include "TEngine.h"

using sharedActor	= std::shared_ptr<AActor>;
using TArray		= std::vector<sharedActor>;
using TMap			= std::map<std::wstring, sharedActor>;

class ANpcCharacter;
class APlayerCharacter;
class ATimerEffect;

struct TEffect
{
	bool					m_bDraw = true; // Draw flag	
	std::wstring			m_szName;
	float					m_fStep = 1.0f;
	UINT					m_iCurrentIndex = 0;
	float					gTimer = 0.0f;
	UINT				    m_iSecond = 0;
	TVector2				m_pInitPos;
	TVector2				m_pInitSize;
	ASprite*				m_pEffect = nullptr; // Effect object pointer
	void   Render()
	{
		m_pEffect->m_pInitPos = m_pInitPos;
		m_pEffect->m_pInitSize = m_pInitSize;
		m_pEffect->m_iCurrentIndex = m_iCurrentIndex;
		m_pEffect->Render();
	}

	void   Tick()
	{
		gTimer += g_fSPF;
		if (gTimer >= m_fStep)
		{
			m_iCurrentIndex++;
			gTimer = gTimer - m_fStep;

			UINT iMaxCounter = m_pEffect->m_texlist.size();
			if (iMaxCounter == 0)
			{
				iMaxCounter = m_pEffect->m_uvlist.size();
				
			}
			if (m_iCurrentIndex >= iMaxCounter)
			{
				m_bDraw = false; 
				m_iCurrentIndex = 0;	
				gTimer = 0.0f;
			}
		}
		//m_pEffect->m_fAngle = g_fGameTimer;
		//m_pEffect->m_vScale = { cosf(g_fGameTimer), cosf(g_fGameTimer) };
	}
};


class UWorld : public UObject
{
public:
	int				m_iNumMissionClear = 0;
	static std::shared_ptr<APlayerCharacter> m_pPlayer;
	std::vector<ASprite*>	m_Effects;
	std::vector<ASprite*>	m_EffectListTex;
	std::vector<ASprite*>	m_EffectListUV;
	UINT			m_iCurrentIndex = 0;	
	TMap			m_ActorList;
	std::list<std::shared_ptr<AActor>>	m_Projectile;
	std::vector<std::shared_ptr<TEffect>>	m_EffectList;	
	// 0  ~  100;  [0]false ~ 10-> [10]true, 1 ~ 9, : [10]false
public:
	void			Init();
	void			Tick();
	void			AddEffectTex(TVector2 pos);
	void			AddEffectUV(TVector2 pos);
	void			AddEffect(TVector2 pos);
	void			Render();
	void			Release();
public:
	virtual ~UWorld();
};

