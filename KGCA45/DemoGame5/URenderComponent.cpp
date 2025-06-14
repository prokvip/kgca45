#include "URenderComponent.h"
#include "TDevice.h"
#include "AActor.h"
bool   TTexture::Load(TString filename)
{
	// 제외 포멧 :  tga, gif
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

URenderComponent::URenderComponent()
{
}

URenderComponent::URenderComponent(TString name) : UActorComponent(name)
{
}
URenderComponent::~URenderComponent()
{
	if (m_pTexture) m_pTexture->Release();
	if (m_pSRV) m_pSRV->Release();
	if (m_pVSBuf) m_pVSBuf->Release();
	if (m_pPSBuf) m_pPSBuf->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
}
bool   URenderComponent::SetTexture(TString filename)
{
	// 제외 포멧 :  tga, gif
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
void   URenderComponent::UpdateVertexBuffer()
{
	if (m_pVertexBuffer)
	{
		TDevice::m_pContext->UpdateSubresource(
			m_pVertexBuffer, 0, nullptr,
			&m_VertexList.at(0), 0, 0);
	}
}
bool     URenderComponent::Create(TVector2 pos, TVector2 size,
	TString texfilepath,
	TString shaderfilepath)
{
	GetOwner()->SetRect(pos, size);
	CreateVertexData();
	CreateVertexBuffer();
	SetTexture(texfilepath);
	CreateVertexShader(shaderfilepath);
	CreatePixelShader(shaderfilepath);
	CreateVertexLayout();
	return true;
}
bool		URenderComponent::CreateVertexLayout()
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
HRESULT		URenderComponent::D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
	LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
	ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult)
{
	HRESULT hr = S_OK;
	hr = D3DCompileFromFile(pSrcFile, pDefines, pInclude, pFunctionName, pProfile, Flags1, Flags2, ppShader, ppErrorMsgs);
	return hr;
}
// C++ : MSVC 컴파일러로 컴파일한다.
// HLSL(Hight Level Shader Language) : 고급쉐이더 언어(컴파일)
bool		URenderComponent::CreateVertexShader(TString filename)
{
	HRESULT hr = S_OK;
	// L"hlsl.txt"을 로딩하여 "VS" 함수를 vs_5_0컴파일러로 컴파일한다.
	// 컴파일 결과(오브젝트파일)가 m_pVSBuf에 저장된다.
	DWORD dwShaderFlags = 0;// D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pBufferErrors = NULL;
	if (FAILED(hr = D3DX11CompileFromFile(filename.c_str(), NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0",
		dwShaderFlags, NULL, &m_pVSBuf, &pBufferErrors, NULL)))
	{
		PrintDetailA("%s:%s\n", (char*)pBufferErrors->GetBufferPointer(),
			L"URenderComponent::CreateVertexShader()");
		if (pBufferErrors)pBufferErrors->Release();
		return false;
	}
	hr = TDevice::m_pd3dDevice->CreateVertexShader(
		(DWORD*)m_pVSBuf->GetBufferPointer(),
		m_pVSBuf->GetBufferSize(), NULL,
		&m_pVertexShader);
	if (FAILED(hr))
	{
		TDevice::DX_CHECK(hr, L"URenderComponent::CreatePixelShader() ");
		return false;
	}
	return true;
}
bool		URenderComponent::CreatePixelShader(TString filename)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pBufferErrors = NULL;
	if (FAILED(hr = D3DX11CompileFromFile(filename.c_str(), NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0",
		dwShaderFlags, NULL, &m_pPSBuf, &pBufferErrors, NULL)))
	{
		PrintDetailA("%s:%s\n", (char*)pBufferErrors->GetBufferPointer(),
			L"URenderComponent::CreateVertexShader()");
		if (pBufferErrors)pBufferErrors->Release();
		return false;
	}
	hr = TDevice::m_pd3dDevice->CreatePixelShader(
		(DWORD*)m_pPSBuf->GetBufferPointer(),
		m_pPSBuf->GetBufferSize(), NULL,
		&m_pPixelShader);
	if (FAILED(hr))
	{
		TDevice::DX_CHECK(hr, L"URenderComponent::CreatePixelShader() ");
		return false;
	}
	return true;
}

TVector2 URenderComponent::ScreenToNDC(TVector2& p)
{
	// NDC
	// screen x:0 ~ 800, y=0 ~ 600
	// screen x:0 ~ 1,   y=0 ~ 1
	// ndc    x:-1 ~ +1, y=-1 ~ +1
	// 
	// ndc    x:-1 ~ +1, y=-1 ~ +1
	TVector2 tRet;
	tRet.x = p.x / 800.0f;
	tRet.y = p.y / 600.0f;
	tRet.x = tRet.x * 2.0f - 1.0f;
	tRet.y = (tRet.y * 2.0f - 1.0f) * -1.0f;
	return tRet;
}
// 시스템메모리에 할당 및 저장한다.
void     URenderComponent::CreateVertexData()
{
	if (m_VertexList.size() == 0)
	{
		m_VertexList.resize(6);
	}
	TRect  rt = GetOwner()->GetRect();
	// ltrb
	// v0(l,t)             v1(r,t),v4


	// v2(l,b),v3          v5(r,b)
	///////////////////// 텍스처 좌표 ////////////////////
	//텍스처의 크기에 상관없이 왼쪽은 0, 오른쪽 1
	// v0(0.0f,0.0f)       v1(1.0f,0.0f)


	// v2(0.0f, 1.0f)      v5(1.0f,1.0f)
	m_VertexList[0].p = { rt[0], rt[1] };
	m_VertexList[0].c = { 1.0f,1.0f,1.0f,1.0f };
	m_VertexList[0].t = { 0.0f,0.0f };
	m_VertexList[1] = { { rt[2], rt[1] },{ 1.0f,1.0f,1.0f,1.0f }, {1.0f,0.0f} };
	m_VertexList[2] = { TVector2(rt[0],rt[3]),
							TColor(1.0f,1.0f,1.0f,1.0f),
							TVector2(0.0f, 1.0f) };
	m_VertexList[5].p = TVector2(rt[2], rt[3]);
	m_VertexList[5].c = TColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[5].t = TVector2(1.0f, 1.0f);
	m_VertexList[3] = m_VertexList[2];
	m_VertexList[4] = m_VertexList[1];
	// NDC
	/*for (auto& v : m_VertexList)
	{
		v.p = ScreenToNDC(v.p);
	}*/
}
void     URenderComponent::UpdatePositionVertexData()
{
	if (m_VertexList.size() == 0)
	{
		return;
	}
	TRect  rt = GetOwner()->GetRect();
	m_VertexList[0].p = { rt[0], rt[1] };
	m_VertexList[1].p = { rt[2], rt[1] };
	m_VertexList[2].p = { rt[0], rt[3] };
	m_VertexList[3].p = { rt[0], rt[3] };
	m_VertexList[4].p = { rt[2], rt[1] };
	m_VertexList[5].p = { rt[2], rt[3] };
	UpdateVertexBuffer();
}
void   URenderComponent::UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v3)
{
	if (m_VertexList.size() == 0)
	{
		return;
	}
	m_VertexList[0].c = v0;
	m_VertexList[1].c = v1;
	m_VertexList[2].c = v2;
	m_VertexList[5].c = v3;
	m_VertexList[3].c = m_VertexList[2].c;
	m_VertexList[4].c = m_VertexList[1].c;
	UpdateVertexBuffer();
}
void   URenderComponent::UpdateUVVertexData(TVector2 p, TVector2 s)
{
	if (m_VertexList.size() == 0)
	{
		return;
	}
	m_VertexList[0].t = { p.x / (float)m_TexDesc.Width, p.y / (float)m_TexDesc.Height };
	m_VertexList[1].t = { (p.x + s.x) / (float)m_TexDesc.Width, m_VertexList[0].t.y };
	m_VertexList[2].t = { m_VertexList[0].t.x, (p.y + s.y) / (float)m_TexDesc.Height };
	m_VertexList[5].t = { m_VertexList[1].t.x, m_VertexList[2].t.y };
	m_VertexList[3].t = m_VertexList[2].t;
	m_VertexList[4].t = m_VertexList[1].t;
	UpdateVertexBuffer();
}
// GPU 메모리에 할당 및 저장한다.
bool     URenderComponent::CreateVertexBuffer()
{
	// 할당	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(TVertex) * m_VertexList.size();// 할당크기
	bd.Usage = D3D11_USAGE_DEFAULT;//GPU 메모리에 할당
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 정점버퍼로
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
		TDevice::DX_CHECK(hr, L"URenderComponent::CreateVertexBuffer");
		return false;
	}
	return true;
}


void   URenderComponent::Render()
{
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	TDevice::m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pVertexLayout);
	TDevice::m_pContext->VSSetShader(m_pVertexShader, nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pPixelShader, nullptr, 0);
	TDevice::m_pContext->PSSetShaderResources(0, 1, &m_pSRV);
	TDevice::m_pContext->Draw(m_VertexList.size(), 0);
}