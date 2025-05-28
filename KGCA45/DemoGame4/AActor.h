#pragma once
#include "UObject.h"
/// <summary>
/// ��(����ȭ��)�� ��ġ�Ǵ� ������Ʈ
/// </summary>

class AActor : public UObject
{
protected:
	TPoint						m_Position;
	TRect						m_rt;	
	float 						m_fSpeed = 100.0f;
public:
	virtual TPoint GetPosition() {
		return m_Position;
	};
	virtual TRect  GetRect() {
		return m_rt;
	};
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

