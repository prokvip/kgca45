#pragma once
#include "AActor.h"
#include "TDevice.h"

class UBackground :  public AActor
{
protected:
	ID3D11Buffer*		m_pVertexBuffer = nullptr;
	ID3D11InputLayout*	m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader*	m_pPixelShader = nullptr;
	ID3DBlob*			m_pVSBuf = NULL;
	ID3DBlob*			m_pPSBuf = NULL;	
	ID3D11Texture2D*			m_pTexture = nullptr;
	ID3D11ShaderResourceView*	m_pSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_TexDesc;
public:
	std::vector<TVertex>  m_VertexList;
	ID3D11Buffer* GetVB() { return m_pVertexBuffer; }
	virtual bool   SetTexture(TString filename);
	virtual void   UpdatePositionVertexData();
	virtual void   UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v3);
	virtual void   UpdateUVVertexData(TPoint p, TPoint s);
	virtual void   UpdateVertexBuffer() override;
	TPoint	 ScreenToNDC(TPoint& p);
	virtual	bool     Create(
		TPoint pos, 
		TPoint size,
		TString texfilepath,
		TString shaderfilepath);
	virtual void     CreateVertexData();
	virtual bool     CreateVertexBuffer();
	virtual bool     CreateVertexLayout();
	virtual bool     CreateVertexShader(TString filename);
	virtual bool     CreatePixelShader(TString filename);
	virtual void   Render() override;

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
	/*virtual void     CreateVertexData() override
	{
		m_VertexList.resize(6);
		TRect  rt = GetRect();
		m_VertexList[0].p = { rt[0], rt[1] };
		m_VertexList[0].c = { 1.0f,1.0f,1.0f,1.0f };
		m_VertexList[0].t = { 0.0f,0.0f };
		m_VertexList[1].p = { rt[2], rt[1] };
		m_VertexList[1].c = { 1.0f,1.0f,1.0f,1.0f };
		m_VertexList[1].t = { 1.0f,0.0f };
		m_VertexList[2].p = { rt[0],rt[3] };
		m_VertexList[2].c = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_VertexList[2].t = { 0.0f, 1.0f };
		m_VertexList[5].p = { rt[2], rt[3] };
		m_VertexList[5].c = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_VertexList[5].t = { 1.0f, 1.0f };
		m_VertexList[3] = m_VertexList[2];
		m_VertexList[4] = m_VertexList[1];	
	}*/
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