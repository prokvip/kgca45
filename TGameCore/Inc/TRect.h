#pragma once
#include "TVector.h"
#include "TMatrix.h"
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
	float     m_fTop;
	float     m_fLeft;
	float     m_fRight;
	float     m_fBottom;
	float     m_fWidth;
	float     m_fHeight;
	TVector2    m_tStart;	//  m_fLeft,m_fTop
	TVector2    m_tSize;	//  m_fWidth,m_fHeight
	TVector2    m_tCenter;
public:
	float    operator[] (int iIndex);
	const TVector2 GetStart() { 		
		return m_tStart; 
	}
	const TVector2 GetSize() {		
		return m_tSize; 
	}
	const TVector2 GetCenter() {		
		return m_tCenter;
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

