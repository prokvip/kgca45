#include "TRect.h"
#include <Windows.h>
#include <iostream>
float    TRect::operator[] (int iIndex)
{
	float fRet = m_fLeft;
	if (iIndex == 1) fRet = m_fTop;
	if (iIndex == 2) fRet = m_fRight;
	if (iIndex == 3) fRet = m_fBottom;
	return fRet;
}
TRect::TRect(void)
{
	SetRect(0, 0, 0, 0);	
}
TRect::TRect(TVector2 pos, TVector2 size)
{
	SetRect(pos.x, pos.y, size.x, size.y);	
}
TRect::TRect(float l, float t, float r, float b)
{
	SetRect(l, t, r, b);	// 영역을 주어진 값으로 초기화
}
void TRect::SetRect(TVector2 pos, TVector2 size)
{
	SetRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
}
void TRect::SetRect(float l, float t, float r, float b)
{
	m_fLeft = l;		// 시작점의 x좌표 설정
	m_fTop = t;			// 시작점의 y좌표 설정
	m_fRight = r;		// 끝점의 x좌표 설정
	m_fBottom = b;		// 끝점의 y좌표 설정
	m_tPos.x = l;
	m_tPos.y = t;
	m_tSize.x = r-l;
	m_tSize.y = b-t;
}
float TRect::GetWidth() const
{
	return m_fRight - m_fLeft;
}
const float TRect::GetHeight() const
{
	return m_fBottom - m_fTop;
}
void TRect::GetStartPoint(float& x, float& y) const
{
	m_iMutable = 3;
	x = m_fLeft;		// 시작점의 x 좌표 얻기
	y = m_fTop;		// 시작점의 y좌표 얻기
}
void TRect::GetEndPoint(float& x, float& y) const
{
	x = m_fRight;		// 끝점의 x 좌표 얻기
	y = m_fBottom;		// 끝점의 y좌표 얻기
}
void TRect::GetCenterPoint(float& x, float& y) const
{
	x = (m_fLeft + m_fRight) / 2;	// 중심점의 x 좌표 얻기
	y = (m_fTop + m_fBottom) / 2;	// 중심점의 y좌표 얻기
}

bool TRect::IsPointInRegion(float x, float y) const
{
	return (x >= m_fLeft && x <= m_fRight && y >= m_fTop && y <= m_fBottom);
}
void TRect::Move(float x, float y) {
	m_fLeft += x;			// 시작점의 x좌표 이동
	m_fRight += x;			// 끝점의 x좌표 이동
	m_fTop += y;			// 시작점의 y좌표 이동
	m_fBottom += y;		// 끝점의 y좌표 이동

	m_tPos.x = m_fLeft;
	m_tPos.y = m_fTop;
	m_tSize.x = m_fRight - m_fLeft;
	m_tSize.y = m_fBottom - m_fTop;
}
void TRect::Resize(float width, float height)
{
	float x, y;
	GetCenterPoint(x, y);	// 중심점 좌표 얻기
	m_fLeft = x - width / 2;	// 중심으로부터 가로길이의 절반만큼 이동
	m_fTop = y - height / 2;	// 중심으로부터 세로길이의 절반만큼 이동
	m_fRight = m_fLeft + width;	// 가로길이가 width가 되도록 조절
	m_fBottom = m_fTop + height;	// 세로길이가 height가 되도록 조절
	m_tPos.x = m_fLeft;
	m_tPos.y = m_fTop;
	m_tSize.x = m_fRight - m_fLeft;
	m_tSize.y = m_fBottom - m_fTop;
}
void TRect::UnionRegion(const TRect& r1, const TRect& r2)
{
	m_fLeft = r1.m_fLeft < r2.m_fLeft ? r1.m_fLeft : r2.m_fLeft;
	m_fRight = r1.m_fRight > r2.m_fRight ? r1.m_fRight : r2.m_fRight;
	m_fTop = r1.m_fTop < r2.m_fTop ? r1.m_fTop : r2.m_fTop;
	m_fBottom = r1.m_fBottom > r2.m_fBottom ? r1.m_fBottom : r2.m_fBottom;
}
bool TRect::IntersectRegion(const TRect& r1, const TRect& r2)
{
	m_fLeft = r1.m_fLeft > r2.m_fLeft ? r1.m_fLeft : r2.m_fLeft;
	m_fRight = r1.m_fRight < r2.m_fRight ? r1.m_fRight : r2.m_fRight;
	m_fTop = r1.m_fTop > r2.m_fTop ? r1.m_fTop : r2.m_fTop;
	m_fBottom = r1.m_fBottom < r2.m_fBottom ? r1.m_fBottom : r2.m_fBottom;
	// 한점 또는 라인이 중첩되었을 때 교차로 판정하지 않았다. 
	// 교집합이 존재하지 않는 경우
	if (m_fLeft >= m_fRight || m_fTop >= m_fBottom)
	{
		m_fLeft = m_fTop = m_fRight = m_fBottom = 0;
		return false;
	}
	return true;
}

void TRect::Show(void)
{
	std::wcout  << L" l= " << m_fLeft << L" t= " << m_fTop 
				<< L" r= " << m_fRight << L" b= " << m_fBottom 
				<< L" w= " << GetWidth() << L" h= " << GetHeight() << std::endl;
}
