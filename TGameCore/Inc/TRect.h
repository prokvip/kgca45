#pragma once
#include "TVector.h"
#include "TMatrix.h"
// 화면상단좌측이 원점
// [l,t]0,0        ->X축         [r,t]800,0
// y축
// [l,b]600,0      ->            [r,b]800,600

// point       ->X축       width
// y축
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
	// 사각형 영역에 대한 정보를 얻는 함수들
	const float GetLeft() { return m_fLeft; }
	const float GetTop() { return m_fTop; }
	const float* GetRight() { return &m_fRight; }
	const float& GetBottom() { return m_fBottom; }

	float GetWidth() const;						// 가로길이 얻기	
	const float GetHeight() const;				// 세로길이 얻기
	void GetStartPoint(float& x, float& y) const;	// 시작점 얻기
	void GetEndPoint(float& x, float& y) const;		// 끝점 얻기
	void GetCenterPoint(float& x, float& y) const;	// 중심점 얻기
	bool IsPointInRegion(float x, float y) const;	// 점이 영역 안에 있는지
	/////////////////////////////////////////////////////////////
	// 사각형 영역을 설정하고 처리하는 함수들
	void SetRect(TVector2 pos, TVector2 size);
	void SetRect(float l, float t, float r, float b);	// 영역 설정
	void Move(float x, float y);					// 위치 이동
	void Resize(float width, float height);			// 크기 변경
	void UnionRegion(const TRect& r1, const TRect& r2);		// 합집합
	bool IntersectRegion(const TRect& r1, const TRect& r2);	// 교집합
	/////////////////////////////////////////////////////////////
	// 사각형 영역을 표시하기 위한 함수들
	void Show(void);						// 영역 출력
public:
	TRect(void);			// 생성자
	TRect(float l, float t, float r, float b);	// 생성자
	TRect(TVector2 pos, TVector2 size);	// 생성자
};

