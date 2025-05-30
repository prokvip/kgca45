#pragma once
#include "UBackground.h"
class TTexture
{
public:
	ID3D11Texture2D*			m_pTexture = nullptr;
	ID3D11ShaderResourceView*	m_pSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_TexDesc;
	virtual bool   Load(TString filename);
	TTexture(TString path) : TTexture()
	{
		Load(path);
	}
	TTexture()
	{
		ZeroMemory(&m_TexDesc, sizeof(D3D11_TEXTURE2D_DESC));
	}
	~TTexture()
	{
		if(m_pTexture)  m_pTexture->Release();
		if (m_pSRV)  m_pSRV->Release();
		m_pTexture = nullptr;
		m_pSRV = nullptr;
	}
};
class TTimerEffect :  public UBackground
{
public:
	float					m_fStep = 1.0f;
	std::vector<TTexture>	m_texlist;
	UINT					m_iCurrentIndex=0;
	float					m_Timer= 0.0f;
	UINT				    m_iSecond;
	TVector2					m_pInitPos;
	TVector2					m_pInitSize;
	std::vector<std::shared_ptr<UBackground>> m_SecondObj;
public:
	void    SetTextureList(std::vector< TTexture>& list);
	virtual	bool     Create(
		TVector2 pos,
		TVector2 size,
		TString texfilepath,
		TString shaderfilepath) override;
	virtual void   Tick()override;
	virtual void   Render() override;
};

class TEffect : public TTimerEffect
{
public:
	virtual void   Tick()override;
	virtual void   Render() override;
};