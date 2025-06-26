#pragma once
#include "TScene.h"


class TButton : public AActor
{
public:
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
	void   Tick();
public:
	TButton(std::wstring name) : AActor(name) {}
	TButton() = default;
	~TButton() = default;
};
class TLobbyScene :   public TScene
{
	std::shared_ptr<TButton>  m_StartBtn;
public:
	virtual void Process(APawn* pPlayer);
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Frame()override;
	virtual void Render()override;
	TLobbyScene(TSceneManager* pOwnder) : TScene(pOwnder)
	{
		m_pOwner = pOwnder;
	}
};

