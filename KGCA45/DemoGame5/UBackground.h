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
	virtual void   UpdateUVVertexData(TVector2 p, TVector2 s);
	virtual void   UpdateVertexBuffer() override;
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
	virtual void   Render() override;

	HRESULT D3DX11CompileFromFile(LPCWSTR pSrcFile, CONST D3D_SHADER_MACRO* pDefines, LPD3DINCLUDE pInclude,
		LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2,
		ID3DBlob** ppShader, ID3DBlob** ppErrorMsgs, HRESULT* pHResult);

public:
	UBackground();
	UBackground(TString name);
	~UBackground();
};
class UPlayer : public UBackground
{
public:
	virtual void   Tick() override
	{		
		auto pos = GetPosition();
		auto rt = GetRect();
	}
public:
	UPlayer() {};
	UPlayer(TString name) :UBackground(name) {}
	~UPlayer() {};
};
class UNpc : public UBackground
{

public:
	virtual void   Tick() override
	{
		TVector2 pos = GetPosition();		
		m_vDirection.Normalized();
		pos = pos + m_vDirection * m_fSpeed * g_fSPF;
		

		if (pos.x > 800.0f) { 
			pos.x = 800.0f; 
			m_vDirection.x *= -1.0f;
		}
		if (pos.x < 0.0f) {
			pos.x = 0.0f;
			m_vDirection.x *= -1.0f;
		}
		if (pos.y > 600.0f) {
			pos.y = 600.0f;
			m_vDirection.y *= -1.0f;
		}
		if (pos.y < 0.0f) {
			pos.y = 0.0f;
			m_vDirection.y *= -1.0f;
		}
		SetPosition(pos);
	}
public:
	UNpc() {  };
	UNpc(TString name) :UBackground(name) {}
	~UNpc() {};
};