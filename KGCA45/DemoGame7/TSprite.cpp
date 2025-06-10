#include "TSprite.h"
#include "TDevice.h"
void    ASprite::SetTextureList(std::vector< TTexture>& list)
{
	m_texlist = list;
}
bool    ASprite::Create(
	TVector2 pos,
	TVector2 size,
	TString texfilepath,
	TString shaderfilepath)
{
	m_pInitPos = pos;
	m_pInitSize = size;
	m_pRenderComponent->Create(pos,size,texfilepath,shaderfilepath);
	return true;
}
void   ASprite::Tick()
{	
	gTimer += g_fSPF;
	if (gTimer >= m_fStep)
	{
		m_iCurrentIndex++;
		gTimer = gTimer- m_fStep;
		if (m_iCurrentIndex >= m_texlist.size())
		{
			m_iCurrentIndex = 0;
		}		
	}
}
void   ASprite::Render()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	auto vb = m_pRenderComponent->GetVB();
	TDevice::m_pContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pRenderComponent->GetVL());
	TDevice::m_pContext->VSSetShader(m_pRenderComponent->GetVS(), nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pRenderComponent->GetPS(), nullptr, 0);
	
	SetRect(m_pInitPos, m_pInitSize);
	UpdatePositionVertexData();
	TDevice::m_pContext->PSSetShaderResources(0, 1, &m_texlist[m_iSecond/10].m_pSRV);
	TDevice::m_pContext->Draw(m_pRenderComponent->m_VertexList.size(), 0);

	SetRect({ m_pInitPos.x+50.0f, m_pInitPos.y }, m_pInitSize);
	UpdatePositionVertexData();
	TDevice::m_pContext->PSSetShaderResources(0, 1,	&m_texlist[m_iSecond%10].m_pSRV);
	TDevice::m_pContext->Draw(m_pRenderComponent->m_VertexList.size(), 0);
}
void   ATimerEffect::Tick()
{
	gTimer += g_fSPF;
	if (gTimer >= 1.0f)
	{
		m_iCurrentIndex++;
		gTimer = gTimer - 1.0f;
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
void   ATimerEffect::Render()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	auto vb = m_pRenderComponent->GetVB();
	TDevice::m_pContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pRenderComponent->GetVL());
	TDevice::m_pContext->VSSetShader(m_pRenderComponent->GetVS(), nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pRenderComponent->GetPS(), nullptr, 0);

	SetRect(m_pInitPos, m_pInitSize);
	UpdatePositionVertexData();
	TDevice::m_pContext->PSSetShaderResources(0, 1, &m_texlist[m_iSecond / 10].m_pSRV);
	TDevice::m_pContext->Draw(m_pRenderComponent->m_VertexList.size(), 0);

	SetRect({ m_pInitPos.x + 50.0f, m_pInitPos.y }, m_pInitSize);
	UpdatePositionVertexData();
	TDevice::m_pContext->PSSetShaderResources(0, 1, &m_texlist[m_iSecond % 10].m_pSRV);
	TDevice::m_pContext->Draw(m_pRenderComponent->m_VertexList.size(), 0);
}
void   AEffectTex::Render()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	auto vb = m_pRenderComponent->GetVB();
	TDevice::m_pContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pRenderComponent->GetVL());
	TDevice::m_pContext->VSSetShader(m_pRenderComponent->GetVS(), nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pRenderComponent->GetPS(), nullptr, 0);

	SetRect(m_pInitPos, m_pInitSize);
	UpdatePositionVertexData();
	TDevice::m_pContext->PSSetShaderResources(0, 1,&m_texlist[m_iSecond % 10].m_pSRV);
	TDevice::m_pContext->Draw(m_pRenderComponent->m_VertexList.size(), 0);
	
}

void   AEffectUV::Render()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	auto vb = m_pRenderComponent->GetVB();
	TDevice::m_pContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pRenderComponent->GetVL());
	TDevice::m_pContext->VSSetShader(m_pRenderComponent->GetVS(), nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pRenderComponent->GetPS(), nullptr, 0);

	SetRect(m_pInitPos, m_pInitSize);
	UpdatePositionVertexData();
	auto srv = m_pRenderComponent->GetSRV();
	TDevice::m_pContext->PSSetShaderResources(0, 1, &srv);
	TDevice::m_pContext->Draw(m_pRenderComponent->m_VertexList.size(), 0);

}