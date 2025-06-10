#pragma once
#include "TStd.h"
class TShader
{	
public:
	ID3D11VertexShader*			m_pVertexShader = nullptr;
	ID3D11PixelShader*			m_pPixelShader = nullptr;
	ID3DBlob*					m_pVSBuf = NULL;
	ID3DBlob*					m_pPSBuf = NULL;
public:
	virtual bool   Load(TString filename);
	bool	CreateVertexShader(TString filename);
	bool	CreatePixelShader(TString filename);
	HRESULT D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
		LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
		ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult);

	TShader(TString path) : TShader()
	{
		Load(path);
	}
	TShader()
	{
		
	}
	~TShader()
	{
		if (m_pVertexShader)	m_pVertexShader->Release();
		if (m_pVSBuf)			m_pVSBuf->Release();
		if (m_pPixelShader)		m_pPixelShader->Release();
		if (m_pPSBuf)			m_pPSBuf->Release();
		m_pVertexShader = nullptr;
		m_pPixelShader = nullptr;
		m_pVSBuf = nullptr;
		m_pPSBuf = nullptr;
	}
};


