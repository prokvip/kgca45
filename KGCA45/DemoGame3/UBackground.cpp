#include "UBackground.h"

UBackground::UBackground() 
{
}

UBackground::UBackground(TString name) : AActor(name)
{
}
UBackground::~UBackground()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
}
bool      UBackground::CreateVertexLayout()
{
	return true;
}
bool      UBackground::CreateVertexShader() {
	return true;
}
bool      UBackground::CreatePixelShader() {
	return true;
}
// 시스템메모리에 할당 및 저장한다.
void     UBackground::CreateVertexData()
{
	m_VertexList.resize(6);
	TRect  rt = GetRect();
	// ltrb
	// v0(l,t)             v1(r,t),v4


	// v2(l,b),v3          v5(r,b)
	m_VertexList[0].p.x = rt[0];
	m_VertexList[0].p.y = rt[1];
	m_VertexList[1].p.x = rt[2];
	m_VertexList[1].p.y = rt[1];
	m_VertexList[2].p.x = rt[0];
	m_VertexList[2].p.y = rt[3];

	m_VertexList[3].p.x = rt[0];
	m_VertexList[3].p.y = rt[3];
	m_VertexList[4].p.x = rt[2];
	m_VertexList[4].p.y = rt[1];
	m_VertexList[5].p.x = rt[2];
	m_VertexList[5].p.y = rt[3];
}
// GPU 메모리에 할당 및 저장한다.
bool     UBackground::CreateVertexBuffer()
{
	// 할당	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(TVertex) * m_VertexList.size();// 할당크기
	bd.Usage=D3D11_USAGE_DEFAULT;//GPU 메모리에 할당
	bd.BindFlags=D3D11_BIND_VERTEX_BUFFER;// 정점버퍼로
	// 저장
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_VertexList.at(0);

	HRESULT hr = TDevice::m_pd3dDevice->CreateBuffer(
		&bd,
		&sd,
		&m_pVertexBuffer);
	if (FAILED(hr))
	{
		TDevice::DX_CHECK(hr, L"UBackground::CreateVertexBuffer");
		return false;
	}
	return true;
}


void   UBackground::Show()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	TDevice::m_pContext->IASetVertexBuffers(0, 1,&m_pVertexBuffer, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pVertexLayout);

	TDevice::m_pContext->VSSetShader(m_pVertexShader, nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pPixelShader, nullptr, 0);	

	TDevice::m_pContext->Draw(m_VertexList.size(), 0);
}