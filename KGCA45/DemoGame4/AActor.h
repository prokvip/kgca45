#pragma once
#include "UObject.h"
/// <summary>
/// 씬(게임화면)에 배치되는 오브젝트
/// </summary>

class AActor : public UObject
{
protected:
	TPoint						m_Position;
	TRect						m_rt;
	ID3D11Texture2D*			m_pTexture = nullptr;
	ID3D11ShaderResourceView*	m_pSRV = nullptr;
	float 						m_fSpeed = 100.0f;
public:
	virtual TPoint GetPosition() {
		return m_Position;
	};
	virtual TRect  GetRect() {
		return m_rt;
	};
	virtual bool   SetTexture(TString filename);
	virtual void   SetPosition(TPoint pos);
	virtual void   SetPosition(float x, float y);
	virtual void   SetRect(TPoint pos, TPoint size);
	virtual void   SetRect(float x, float y, float w, float h);
	virtual void   Move(float x, float y);
	virtual void   Tick();
	virtual void   Render();
	virtual void   UpdateVertexBuffer();
public:
	AActor(std::wstring name);
	AActor();
	~AActor();
};

