#include "TShader.h"
#include "TDevice.h"
bool   TShader::Load(TString filename)
{
	if (true == CreateVertexShader(filename))
	{
		if (true == CreatePixelShader(filename))
		{
			return true;
		}
		else
		{
			PrintDetailA("CreatePixelShader() failed\n");
			return false;
		}
	}
	else
	{
		PrintDetailA("CreateVertexShader() failed\n");
		return false;
	}
	return false;
}
bool		TShader::CreateVertexShader(TString filename)
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
bool		TShader::CreatePixelShader(TString filename)
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

HRESULT		TShader::D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
	LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
	ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult)
{
	HRESULT hr = S_OK;
	hr = D3DCompileFromFile(pSrcFile, pDefines, pInclude, pFunctionName, pProfile, Flags1, Flags2, ppShader, ppErrorMsgs);
	return hr;
}