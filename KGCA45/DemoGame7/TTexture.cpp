#include "TTexture.h"
#include "TDevice.h"
bool   TTexture::Load(TString filename)
{
	// Á¦¿Ü Æ÷¸ä :  tga, gif
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		TDevice::m_pd3dDevice, TDevice::m_pContext,
		filename.c_str(),
		(ID3D11Resource**)&m_pTexture,
		&m_pSRV
	);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			TDevice::m_pd3dDevice, TDevice::m_pContext,
			filename.c_str(),
			(ID3D11Resource**)&m_pTexture,
			&m_pSRV
		);
		if (FAILED(hr))
		{
			return false;
		}
	}
	m_pTexture->GetDesc(&m_TexDesc);
	return true;
}