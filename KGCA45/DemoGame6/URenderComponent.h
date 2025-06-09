#pragma once
#include "UActorComponent.h"

class TTexture
{
	
public:
	ID3D11Texture2D* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_TexDesc;
	virtual bool   Load(TString filename);
	TTexture(TString path) : TTexture()
	{
		Load(path);
	}
	TTexture()
	{
		ZeroMemory(&m_TexDesc, sizeof(D3D11_TEXTURE2D_DESC));
	}
	~TTexture()
	{
		if (m_pTexture)  m_pTexture->Release();
		if (m_pSRV)  m_pSRV->Release();
		m_pTexture = nullptr;
		m_pSRV = nullptr;
	}
};
class URenderComponent :   public UActorComponent
{
protected:
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3DBlob* m_pVSBuf = NULL;
	ID3DBlob* m_pPSBuf = NULL;
	ID3D11Texture2D* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_TexDesc;
public:
	ID3D11Buffer*		GetVB() {return m_pVertexBuffer;}
	ID3D11InputLayout*	GetVL() { return m_pVertexLayout; }
	ID3D11VertexShader* GetVS() { return m_pVertexShader; }
	ID3D11PixelShader*	GetPS() { return m_pPixelShader; }
public:
	std::vector<TVertex>  m_VertexList;
	virtual bool   SetTexture(TString filename);
	virtual void   UpdatePositionVertexData();
	virtual void   UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v3);
	virtual void   UpdateUVVertexData(TVector2 p, TVector2 s);
	virtual void   UpdateVertexBuffer();
	TVector2	 ScreenToNDC(TVector2& p);
	virtual	bool     Create(
		TVector2 pos,
		TVector2 size,
		TString texfilepath,
		TString shaderfilepath);
	virtual void     CreateVertexData();
	virtual bool     CreateVertexBuffer();
	virtual bool     CreateVertexLayout();
	virtual bool     CreateVertexShader(TString filename);
	virtual bool     CreatePixelShader(TString filename);
	virtual void	 Render();

	HRESULT D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
		LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
		ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult);

public:
	URenderComponent();
	URenderComponent(TString name);
	~URenderComponent();
};

