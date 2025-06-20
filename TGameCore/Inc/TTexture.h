#pragma once
#include "TStd.h"
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
		if (m_pTexture)  m_pTexture->Release();

		if (m_pSRV)  m_pSRV->Release();
		m_pTexture = nullptr;
		m_pSRV = nullptr;
	}
};

