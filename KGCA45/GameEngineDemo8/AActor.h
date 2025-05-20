#pragma once
#include "UObject.h"
/// <summary>
/// 씬(게임화면)에 배치되는 오브젝트
/// </summary>

class AActor : public UObject
{
	TPoint   m_Position;
	TRect    m_rt;
public:
	virtual void   SetPosition(TPoint pos);
	virtual void   SetPosition(float x, float y);
	virtual void   SetRect(TPoint pos, TPoint size);
	virtual void   SetRect(float x, float y, float w, float h);
	virtual void   Move(float x, float y);
	virtual void   Tick();
	virtual void   Show();
public:
	AActor(std::wstring name);
	AActor();
	~AActor();
};

