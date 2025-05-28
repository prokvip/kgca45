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
void   UBackground::UpdateVertexBuffer()
{
	UpdatePositionVertexData();
	// vertexbuffer 갱신한다.
	if (m_pVertexBuffer)
	{
		TDevice::m_pContext->UpdateSubresource(
			m_pVertexBuffer, 0, nullptr,
			&m_VertexList.at(0), 0, 0);
	}
}
bool     UBackground::Create(TPoint pos, TPoint size, 
			TString texfilepath, 
			TString shaderfilepath)
{
	SetRect(pos, size);
	CreateVertexData();
	CreateVertexBuffer();
	SetTexture(texfilepath);
	CreateVertexShader(shaderfilepath);
	CreatePixelShader(shaderfilepath);
	CreateVertexLayout();
	return true;
}
bool		UBackground::CreateVertexLayout()
{
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POS",   0, DXGI_FORMAT_R32G32_FLOAT,		   0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, 8,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",   0, DXGI_FORMAT_R32G32_FLOAT,        0, 24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
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
// C++ : MSVC 컴파일러로 컴파일한다.
// HLSL(Hight Level Shader Language) : 고급쉐이더 언어(컴파일)
bool		UBackground::CreateVertexShader(TString filename) 
{
	HRESULT hr=S_OK;
	// L"hlsl.txt"을 로딩하여 "VS" 함수를 vs_5_0컴파일러로 컴파일한다.
	// 컴파일 결과(오브젝트파일)가 m_pVSBuf에 저장된다.
	DWORD dwShaderFlags = 0;// D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pBufferErrors = NULL;
	if (FAILED(hr =D3DX11CompileFromFile(filename.c_str(), NULL,
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
bool		UBackground::CreatePixelShader(TString filename)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pBufferErrors = NULL;
	if (FAILED(hr = D3DX11CompileFromFile(filename.c_str(), NULL,
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
// 시스템메모리에 할당 및 저장한다.
void     UBackground::CreateVertexData()
{
	if (m_VertexList.size() == 0)
	{
		m_VertexList.resize(6);
	}
	TRect  rt = GetRect();
	// ltrb
	// v0(l,t)             v1(r,t),v4


	// v2(l,b),v3          v5(r,b)
	///////////////////// 텍스처 좌표 ////////////////////
	//텍스처의 크기에 상관없이 왼쪽은 0, 오른쪽 1
	// v0(0.0f,0.0f)       v1(1.0f,0.0f)


	// v2(0.0f, 1.0f)      v5(1.0f,1.0f)
	m_VertexList[0].p	= { rt[0], rt[1] };
	m_VertexList[0].c	= { 1.0f,1.0f,1.0f,1.0f };
	m_VertexList[0].t	= { 0.0f,0.0f };
	m_VertexList[1]		= { { rt[2], rt[1] },{ 1.0f,1.0f,1.0f,1.0f }, {1.0f,0.0f} };
	m_VertexList[2]		= {	TPoint(rt[0],rt[3]),
							TColor(1.0f,1.0f,1.0f,1.0f),
						    TPoint(0.0f, 1.0f)};
	m_VertexList[5].p	= TPoint(rt[2], rt[3]);
	m_VertexList[5].c	= TColor(1.0f,1.0f,1.0f,1.0f);
	m_VertexList[5].t   = TPoint(1.0f, 1.0f);
	m_VertexList[3] = m_VertexList[2];
	m_VertexList[4] = m_VertexList[1];
	// NDC
	/*for (auto& v : m_VertexList)
	{
		v.p = ScreenToNDC(v.p);
	}*/
}
void     UBackground::UpdatePositionVertexData()
{
	if (m_VertexList.size() == 0)
	{
		return;
	}
	TRect  rt = GetRect();
	m_VertexList[0].p = { rt[0], rt[1] };
	m_VertexList[1].p = { rt[2], rt[1] };
	m_VertexList[2].p = { rt[0], rt[3] };
	m_VertexList[3].p = { rt[0], rt[3] };
	m_VertexList[4].p = { rt[2], rt[1] };
	m_VertexList[5].p = { rt[2], rt[3] };
}
void   UBackground::UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v2)
{
}
void   UBackground::UpdateUVVertexData(TPoint p, TPoint s)
{
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


void   UBackground::Render()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	TDevice::m_pContext->IASetVertexBuffers(0, 1,&m_pVertexBuffer, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pVertexLayout);
	TDevice::m_pContext->VSSetShader(m_pVertexShader, nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pPixelShader, nullptr, 0);	
	TDevice::m_pContext->PSSetShaderResources(0, 1, &m_pSRV);
	TDevice::m_pContext->Draw(m_VertexList.size(), 0);
}