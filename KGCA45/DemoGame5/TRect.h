#pragma once
#include "TVector.h"
// ȭ���������� ����
// [l,t]0,0        ->X��         [r,t]800,0
// y��
// [l,b]600,0      ->            [r,b]800,600

// point       ->X��       width
// y��
// bottom      ->          width, height
class TRect
{
public:
	mutable int m_iMutable;
private:
	// m_fTop=10, m_fLeft=10, m_fRight=100, m_fBottom=50
	float     m_fTop;
	float     m_fLeft;
	float     m_fRight;
	float     m_fBottom;
	// m_fPos.x=10, m_fPos.y=10, m_fSize.x=90, m_fSize.y=40
	TVector2    m_tPos; //  m_fLeft,m_fTop
	TVector2    m_tSize;//  m_fWidth, m_fHeight
public:
	float    operator[] (int iIndex);
	const TVector2 GetPos() { 
		m_tPos = { m_fLeft, m_fTop };
		return m_tPos; 
	}
	const TVector2 GetSize() {
		m_tPos = { m_fRight-m_fLeft, m_fBottom-m_fTop };
		return m_tSize; 
	}

	const TRect* Get() const { return this; }
	const TRect& GetRef() const { return *this; }
	/////////////////////////////////////////////////////////////
	// �簢�� ������ ���� ������ ��� �Լ���
	const float GetLeft() { return m_fLeft; }
	const float GetTop() { return m_fTop; }
	const float* GetRight() { return &m_fRight; }
	const float& GetBottom() { return m_fBottom; }

	float GetWidth() const;						// ���α��� ���	
	const float GetHeight() const;				// ���α��� ���
	void GetStartPoint(float& x, float& y) const;	// ������ ���
	void GetEndPoint(float& x, float& y) const;		// ���� ���
	void GetCenterPoint(float& x, float& y) const;	// �߽��� ���
	bool IsPointInRegion(float x, float y) const;	// ���� ���� �ȿ� �ִ���
	/////////////////////////////////////////////////////////////
	// �簢�� ������ �����ϰ� ó���ϴ� �Լ���
	void SetRect(TVector2 pos, TVector2 size);
	void SetRect(float l, float t, float r, float b);	// ���� ����
	void Move(float x, float y);					// ��ġ �̵�
	void Resize(float width, float height);			// ũ�� ����
	void UnionRegion(const TRect& r1, const TRect& r2);		// ������
	bool IntersectRegion(const TRect& r1, const TRect& r2);	// ������
	/////////////////////////////////////////////////////////////
	// �簢�� ������ ǥ���ϱ� ���� �Լ���
	void Show(void);						// ���� ���
public:
	TRect(void);			// ������
	TRect(float l, float t, float r, float b);	// ������
	TRect(TVector2 pos, TVector2 size);	// ������
};

