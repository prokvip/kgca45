#pragma once
#include "AActor.h"
#include "TDevice.h"
struct TColor
{
	float  r;
	float  g;
	float  b;
	float  a;
};
struct TVertex
{
	TPoint p;
	TColor c;
};
class UBackground :  public AActor
{
	ID3D11Buffer*		m_pVertexBuffer = nullptr;
	ID3D11InputLayout*	m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader*	m_pPixelShader = nullptr;

	ID3DBlob*			m_pVSBuf = NULL;
	ID3DBlob*			m_pPSBuf = NULL;
	std::vector<TVertex>  m_VertexList;	

public:
	TPoint	 ScreenToNDC(TPoint& p);
	void     CreateVertexData();
	bool     CreateVertexBuffer();
	bool     CreateVertexLayout();
	bool     CreateVertexShader();
	bool     CreatePixelShader();
	virtual void   Show() override;

	HRESULT D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
		LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
		/*ID3DX11ThreadPump* pPump, */ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult);

public:
	UBackground();
	UBackground(TString name);
	~UBackground();
};

