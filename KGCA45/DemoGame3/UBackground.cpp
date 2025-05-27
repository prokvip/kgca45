#include "UBackground.h"

UBackground::UBackground() 
{
}

UBackground::UBackground(TString name) : AActor(name)
{
}
UBackground::~UBackground()
{
	if (m_pVSBuf) m_pVSBuf->Release();
	if (m_pPSBuf) m_pPSBuf->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
}
bool		UBackground::CreateVertexLayout()
{
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POS",   0, DXGI_FORMAT_R32G32_FLOAT,		    0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, 8,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT iNumElement = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = TDevice::m_pd3dDevice->CreateInputLayout(
		layout, iNumElement,
		m_pVSBuf->GetBufferPointer(), 
		m_pVSBuf->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
HRESULT		UBackground::D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
	LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
	ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult)
{
	HRESULT hr = S_OK;
	hr = D3DCompileFromFile(pSrcFile, pDefines, pInclude, pFunctionName, pProfile, Flags1, Flags2, ppShader, ppErrorMsgs);
	return hr;
}
// C++ : MSVC �����Ϸ��� �������Ѵ�.
// HLSL(Hight Level Shader Language) : ��޽��̴� ���(������)
bool		UBackground::CreateVertexShader() 
{
	HRESULT hr=S_OK;
	// L"hlsl.txt"�� �ε��Ͽ� "VS" �Լ��� vs_5_0�����Ϸ��� �������Ѵ�.
	// ������ ���(������Ʈ����)�� m_pVSBuf�� ����ȴ�.
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pBufferErrors = NULL;
	if (FAILED(hr =D3DX11CompileFromFile(L"hlsl.txt", NULL, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", 
		dwShaderFlags, NULL, &m_pVSBuf, &pBufferErrors, NULL)))
	{
		PrintDetailA("%s:%s\n", (char*)pBufferErrors->GetBufferPointer(),
										L"UBackground::CreateVertexShader()");
		if (pBufferErrors)pBufferErrors->Release();
		return false;
	}
	hr = TDevice::m_pd3dDevice->CreateVertexShader(
		(DWORD*)m_pVSBuf->GetBufferPointer(), 
		m_pVSBuf->GetBufferSize(), NULL,
		&m_pVertexShader);
	if (FAILED(hr))
	{
		TDevice::DX_CHECK(hr, L"UBackground::CreatePixelShader() ");
		return false;
	}
	return true;
}
bool		UBackground::CreatePixelShader() 
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pBufferErrors = NULL;
	if (FAILED(hr = D3DX11CompileFromFile(L"hlsl.txt", NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0",
		dwShaderFlags, NULL, &m_pPSBuf, &pBufferErrors, NULL)))
	{
		PrintDetailA("%s:%s\n", (char*)pBufferErrors->GetBufferPointer(),
								L"UBackground::CreateVertexShader()");
		if (pBufferErrors)pBufferErrors->Release();
		return false;
	}
	hr = TDevice::m_pd3dDevice->CreatePixelShader(
		(DWORD*)m_pPSBuf->GetBufferPointer(),
		m_pPSBuf->GetBufferSize(), NULL,
		&m_pPixelShader);
	if (FAILED(hr))
	{
		TDevice::DX_CHECK(hr, L"UBackground::CreatePixelShader() ");
		return false;
	}	
	return true;
}

TPoint UBackground::ScreenToNDC(TPoint& p)
{
	// NDC
	// screen x:0 ~ 800, y=0 ~ 600
	// screen x:0 ~ 1,   y=0 ~ 1
	// ndc    x:-1 ~ +1, y=-1 ~ +1
	// 
	// ndc    x:-1 ~ +1, y=-1 ~ +1
	TPoint tRet;
	tRet.x = p.x / 800.0f;
	tRet.y = p.y / 600.0f;
	tRet.x = tRet.x * 2.0f - 1.0f;
	tRet.y = (tRet.y * 2.0f - 1.0f) * -1.0f;
	return tRet;
}
// �ý��۸޸𸮿� �Ҵ� �� �����Ѵ�.
void     UBackground::CreateVertexData()
{
	m_VertexList.resize(6);
	TRect  rt = GetRect();
	// ltrb
	// v0(l,t)             v1(r,t),v4


	// v2(l,b),v3          v5(r,b)
	m_VertexList[0].p.x = rt[0];
	m_VertexList[0].p.y = rt[1];
	m_VertexList[0].c.r = 1.0f;
	m_VertexList[0].c.g = 0.0f;
	m_VertexList[0].c.b = 0.0f;
	m_VertexList[0].c.a = 1.0f;
	m_VertexList[1].p.x = rt[2];
	m_VertexList[1].p.y = rt[1];
	m_VertexList[1].c.r = 0.0f;
	m_VertexList[1].c.g = 1.0f;
	m_VertexList[1].c.b = 0.0f;
	m_VertexList[1].c.a = 1.0f;
	m_VertexList[2].p.x = rt[0];
	m_VertexList[2].p.y = rt[3];
	m_VertexList[2].c.r = 0.0f;
	m_VertexList[2].c.g = 0.0f;
	m_VertexList[2].c.b = 0.0f;
	m_VertexList[2].c.a = 1.0f;
	m_VertexList[3].p.x = rt[0];
	m_VertexList[3].p.y = rt[3];
	m_VertexList[2].c = m_VertexList[2].c;
	m_VertexList[4].c = m_VertexList[1].c;
	m_VertexList[4].p.x = rt[2];
	m_VertexList[4].p.y = rt[1];
	
	m_VertexList[5].p.x = rt[2];
	m_VertexList[5].p.y = rt[3];
	m_VertexList[5].c.r = 1.0f;
	m_VertexList[5].c.g = 1.0f;
	m_VertexList[5].c.b = 1.0f;
	m_VertexList[5].c.a = 1.0f;
	// NDC
	for (auto& v : m_VertexList)
	{
		v.p = ScreenToNDC(v.p);
	}
}
// GPU �޸𸮿� �Ҵ� �� �����Ѵ�.
bool     UBackground::CreateVertexBuffer()
{
	// �Ҵ�	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(TVertex) * m_VertexList.size();// �Ҵ�ũ��
	bd.Usage=D3D11_USAGE_DEFAULT;//GPU �޸𸮿� �Ҵ�
	bd.BindFlags=D3D11_BIND_VERTEX_BUFFER;// �������۷�
	// ����
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