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
		UINT stride = sizeof(TVertex);
		UINT offset = 0;
		auto vb = m_pEffect->m_pRenderComponent->GetVB();
		TDevice::m_pContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
		TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		TDevice::m_pContext->IASetInputLayout(m_pEffect->m_pRenderComponent->GetVL());
		TDevice::m_pContext->VSSetShader(m_pEffect->m_pRenderComponent->GetVS(), nullptr, 0);
		TDevice::m_pContext->PSSetShader(m_pEffect->m_pRenderComponent->GetPS(), nullptr, 0);
		m_pEffect->SetRect(m_pInitPos, m_pInitSize);
		m_pEffect->UpdatePositionVertexData();
		TDevice::m_pContext->PSSetShaderResources(0, 1, &m_pEffect->m_texlist[m_iCurrentIndex].m_pSRV);
		TDevice::m_pContext->Draw(m_pEffect->m_pRenderComponent->m_VertexList.size(), 0);
	}


	void   Tick()
	{
		gTimer += g_fSPF;
		if (gTimer >= m_fStep)
		{
			m_iCurrentIndex++;
			gTimer = gTimer - m_fStep;
			if (m_iCurrentIndex >= m_pEffect->m_texlist.size())
			{
				m_iCurrentIndex = 0;
			}			
		}
	}
};


class UWorld : public UObject
{
public:
	std::shared_ptr<APlayerCharacter> m_pPlayer = nullptr;

	std::vector<ASprite*>	effectListTex;
	std::vector<ASprite*>	effectListUV;
	UINT			m_iCurrentIndex = 0;	
	TMap			m_ActorList;
	std::vector<std::shared_ptr<TEffect>>	m_EffectList;

public:
	void			Init();
	void			Tick();
	void			AddEffectTex(TVector2 pos);
	void			AddEffectUV(TVector2 pos);
	void			Render();
};

