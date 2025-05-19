#pragma once
#include "UObject.h"
/// <summary>
/// ��(����ȭ��)�� ��ġ�Ǵ� ������Ʈ
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
	// ���Կ�����
	void operator=(const AActor& comp);
	// ���� ������
	AActor(const AActor& comp);

	AActor(const AActor&& actor);
	void operator=(const AActor&& actor);

	AActor(std::wstring name);
	AActor();
	~AActor();
};

