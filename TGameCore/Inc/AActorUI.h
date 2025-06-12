#pragma once
#include "AActor.h"

/// <summary>
/// 씬(게임화면)에 배치되는 오브젝트
/// </summary>

class AActorUI : public AActor
{
public:
	std::shared_ptr<URenderComponent> m_pRenderComponent = nullptr;
protected:
	TVector2	m_Position;
	TRect		m_rt;
	float 		m_fSpeed = 200.0f;
public:
	bool		m_bDraw = true;
	TVector2	m_vDirection = { 1,-1 };
public:
	virtual TVector2 GetPosition() {
		return m_Position;
	};
	virtual TRect  GetRect() {
		return m_rt;
	};
	virtual void   SetPosition(TVector2 pos);
	virtual void   SetPosition(float x, float y);
	virtual void   SetRect(TVector2 pos, TVector2 size);
	virtual void   SetRect(float x, float y, float w, float h);
	virtual void   Move(float x, float y);
	virtual void   Tick();
	virtual void   Render();
	virtual void   UpdateVertexBuffer();
	virtual void   UpdatePositionVertexData();
	virtual void   UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v3);
	virtual void   UpdateUVVertexData(TVector2 p, TVector2 s);
	virtual	bool     Create(
		TVector2 pos,
		TVector2 size,
		TString texfilepath,
		TString shaderfilepath);
public:
	AActorUI(std::wstring name);
	AActorUI();
	~AActorUI();
};

