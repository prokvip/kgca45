#include "TTimerEffect.h"
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
bool    TTimerEffect::Create(
	TPoint pos,
	TPoint size,
	TString texfilepath,
	TString shaderfilepath)
{
	m_pInitPos = pos;
	m_pInitSize = size;
	m_texlist.reserve(10);
    for (int i = 0; i < 10; i++)
    {
        TString texPath = L"../../data/texture/";
        texPath += std::to_wstring(i);
        texPath += L".png";
		m_texlist.emplace_back(texPath);
    }
	UBackground::Create(pos,size,texfilepath,shaderfilepath);
	return true;
}
void   TTimerEffect::Tick()
{	
	m_Timer += g_fSPF;
	if (m_Timer >= 1.0f)
	{
		m_iCurrentIndex++;
		m_Timer = m_Timer-1.0f;
		if (m_iCurrentIndex >= m_texlist.size())
		{
			m_iCurrentIndex = 0;
		}
		m_iSecond++;
		if (m_iSecond >= 60)
		{
			m_iSecond = 0;
		}
	}
}
void   TTimerEffect::Render()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	TDevice::m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pVertexLayout);
	TDevice::m_pContext->VSSetShader(m_pVertexShader, nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pPixelShader, nullptr, 0);
	
	SetRect(m_pInitPos, m_pInitSize);
	UpdatePositionVertexData();
	TDevice::m_pContext->PSSetShaderResources(0, 1, 
		&m_texlist[m_iSecond/10].m_pSRV);
	TDevice::m_pContext->Draw(m_VertexList.size(), 0);

	SetRect({ m_pInitPos.x+50.0f, 0.0f}, m_pInitSize);
	UpdatePositionVertexData();
	TDevice::m_pContext->PSSetShaderResources(0, 1,
		&m_texlist[m_iSecond%10].m_pSRV);
	TDevice::m_pContext->Draw(m_VertexList.size(), 0);
}