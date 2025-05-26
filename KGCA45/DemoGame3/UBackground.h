#pragma once
#include "AActor.h"
#include "TDevice.h"
struct TVertex
{
	TPoint p;
};
class UBackground :  public AActor
{
	ID3D11Buffer*		m_pVertexBuffer = nullptr;
	ID3D11InputLayout*	m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader*	m_pPixelShader = nullptr;
public:
	std::vector<TVertex>  m_VertexList;
	void     CreateVertexData();
	bool     CreateVertexBuffer();
	bool     CreateVertexLayout();
	bool     CreateVertexShader();
	bool     CreatePixelShader();
	virtual void   Show() override;
public:
	UBackground();
	UBackground(TString name);
	~UBackground();
};

