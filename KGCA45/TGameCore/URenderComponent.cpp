#include "URenderComponent.h"
#include "TDevice.h"
#include "AActor.h"
#include "TEngine.h"

void   URenderComponent::TickComponent()
{
}
URenderComponent::URenderComponent()
{
}
URenderComponent::URenderComponent(TString name) : UActorComponent(name)
{
}
URenderComponent::~URenderComponent()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();	
}
bool   URenderComponent::SetTexture(TString filename)
{
	auto pPoint = TEngine::gTexManager.LoadPtr(filename);
	if (pPoint != nullptr)
	{		
		m_pTexture = pPoint->m_pTexture;
		m_pTexture->GetDesc(&m_TexDesc);
		m_pSRV = pPoint->m_pSRV;
		return true;
	}

	/*TString name;
	if (true==TEngine::gTexManager.Load(filename, name))
	{
		auto pTexClass = TEngine::gTexManager.GetAsset(name);
		m_pTexture = pTexClass->m_pTexture;
		m_pTexture->GetDesc(&m_TexDesc);
		m_pSRV = pTexClass->m_pSRV;
		return true;
	}*/
	return false;
}
bool   URenderComponent::SetTextureMask(TString filename)
{
	auto pPoint = TEngine::gTexManager.LoadPtr(filename);
	if (pPoint != nullptr)
	{
		m_pTextureMask = pPoint->m_pTexture;
		m_pSRVMask = pPoint->m_pSRV;
		return true;
	}
	return false;
}
void   URenderComponent::UpdateVertexBuffer()
{
	GetOwner()->Transform();
	if (m_pVertexBuffer)
	{			
		for (auto& v : m_VertexList)
		{
			v.c.a = m_pOwner->m_fAlpha;
		}
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
	CreateShader(shaderfilepath);
	//CreateVertexShader(shaderfilepath);
	//CreatePixelShader(shaderfilepath);
	CreateVertexLayout();
	return true;
}
bool     URenderComponent::Create(TVector2 pos, TVector2 size,
	TString texfilepath,
	TString texMaskfilepath,
	TString shaderfilepath)
{
	GetOwner()->SetRect(pos, size);
	CreateVertexData();
	CreateVertexBuffer();
	SetTexture(texfilepath);
	SetTextureMask(texMaskfilepath);
	CreateShader(shaderfilepath);
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

// C++ : MSVC 컴파일러로 컴파일한다.
// HLSL(Hight Level Shader Language) : 고급쉐이더 언어(컴파일)

bool		URenderComponent::CreateShader(TString filename)
{
	auto pPoint = TEngine::gShaderManager.LoadPtr(filename);
	if (pPoint != nullptr)
	{
		m_pVertexShader = pPoint->m_pVertexShader;
		m_pPixelShader = pPoint->m_pPixelShader;
		m_pVSBuf = pPoint->m_pVSBuf;
		return true;
	}
	return true;
}
bool		URenderComponent::CreateVertexShader(TString filename)
{
	auto pPoint = TEngine::gShaderManager.LoadPtr(filename);
	if (pPoint != nullptr)
	{
		m_pVertexShader = pPoint->m_pVertexShader;
		return true;
	}	
	return true;
}
bool		URenderComponent::CreatePixelShader(TString filename)
{
	auto pPoint = TEngine::gShaderManager.LoadPtr(filename);
	if (pPoint != nullptr)
	{
		m_pPixelShader = pPoint->m_pPixelShader;
		return true;
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
	tRet.x = p.x / g_rtClient.right;
	tRet.y = p.y / g_rtClient.bottom;
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

	m_InitVertexList = m_VertexList;
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
	UpdateVertexBuffer();
	UINT stride = sizeof(TVertex);
	UINT offset = 0;
	TDevice::m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	TDevice::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	TDevice::m_pContext->IASetInputLayout(m_pVertexLayout);
	TDevice::m_pContext->VSSetShader(m_pVertexShader, nullptr, 0);
	TDevice::m_pContext->PSSetShader(m_pPixelShader, nullptr, 0);
	TDevice::m_pContext->PSSetShaderResources(0, 1, &m_pSRV);
	TDevice::m_pContext->PSSetShaderResources(1, 1, &m_pSRVMask);
	TDevice::m_pContext->Draw(m_VertexList.size(), 0);
}