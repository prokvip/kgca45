#pragma once
#include "AActor.h"
#include "TDevice.h"
struct TColor
{
	float  r;
	float  g;
	float  b;
	float  a;
	TColor() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	TColor(float r, float g, float b, float a) 
	{
		this->r = r; this->g = g; this->b = b; this->a = a;
	}
};
struct TVertex
{
	TPoint p;
	TColor c;
	TVertex() : p{ 0,0 }, c{ 1.0f,1.0f,1.0f,1.0f } {}
	TVertex(TPoint p1, TColor c1) : p(p1), c(c1) {}
	TVertex(float x, float y, float r, float g, float b, float a)
	{
		p.x = x; p.y = y;
		c.r = r; c.g = g; c.b = b; c.a = a;
	}
};
class UBackground :  public AActor
{
protected:
	ID3D11Buffer*		m_pVertexBuffer = nullptr;
	ID3D11InputLayout*	m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader*	m_pPixelShader = nullptr;
	ID3DBlob*			m_pVSBuf = NULL;
	ID3DBlob*			m_pPSBuf = NULL;
	std::vector<TVertex>  m_VertexList;	
public:
	TPoint	 ScreenToNDC(TPoint& p);
	virtual void     CreateVertexData();
	bool     CreateVertexBuffer();
	bool     CreateVertexLayout();
	bool     CreateVertexShader();
	bool     CreatePixelShader();
	virtual void   Show() override;

	HRESULT D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
		LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
		ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult);

public:
	UBackground();
	UBackground(TString name);
	~UBackground();
};

class UUI1 : public UBackground
{
public:
	virtual void     CreateVertexData()
	{		
		m_VertexList.resize(6);
		TRect  rt = GetRect();
		m_VertexList[0].p = { rt[0], rt[1] };
		m_VertexList[0].c = { 1.0f,1.0f,1.0f,1.0f };
		m_VertexList[1] = { { rt[2], rt[1] },{ 1.0f,1.0f,1.0f,1.0f } };
		m_VertexList[2] = { TPoint(rt[0],rt[3]),TColor(1.0f,1.0f,1.0f,1.0f) };
		m_VertexList[5].p = TPoint(rt[2], rt[3]);
		m_VertexList[5].c = TColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_VertexList[3] = m_VertexList[2];
		m_VertexList[4] = m_VertexList[1];	
	}
public:
	UUI1() {};
	UUI1(TString name) :UBackground(name) {}
	~UUI1() {};
};
class UUI2 : public UBackground
{
public:
	UUI2() {};
	UUI2(TString name) :UBackground(name) {}
	~UUI2() {};
};
class UUI3 : public UBackground
{
public:
	UUI3() {};
	UUI3(TString name) :UBackground(name) {}
	~UUI3() {};
};
class UUI4 : public UBackground
{
public:
	UUI4() {};
	UUI4(TString name) :UBackground(name) {}
	~UUI4() {};
};
class UUI5 : public UBackground
{
public:
	UUI5() {};
	UUI5(TString name) :UBackground(name) {}
	~UUI5() {};
};