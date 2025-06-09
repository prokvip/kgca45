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
	SetRect(l, t, r, b);	// ������ �־��� ������ �ʱ�ȭ
}
void TRect::SetRect(TVector2 pos, TVector2 size)
{
	SetRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
}
void TRect::SetRect(float l, float t, float r, float b)
{
	m_fLeft = l;		// �������� x��ǥ ����
	m_fTop = t;			// �������� y��ǥ ����
	m_fRight = r;		// ������ x��ǥ ����
	m_fBottom = b;		// ������ y��ǥ ����
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
	x = m_fLeft;		// �������� x ��ǥ ���
	y = m_fTop;		// �������� y��ǥ ���
}
void TRect::GetEndPoint(float& x, float& y) const
{
	x = m_fRight;		// ������ x ��ǥ ���
	y = m_fBottom;		// ������ y��ǥ ���
}
void TRect::GetCenterPoint(float& x, float& y) const
{
	x = (m_fLeft + m_fRight) / 2;	// �߽����� x ��ǥ ���
	y = (m_fTop + m_fBottom) / 2;	// �߽����� y��ǥ ���
}

bool TRect::IsPointInRegion(float x, float y) const
{
	return (x >= m_fLeft && x <= m_fRight && y >= m_fTop && y <= m_fBottom);
}
void TRect::Move(float x, float y) {
	m_fLeft += x;			// �������� x��ǥ �̵�
	m_fRight += x;			// ������ x��ǥ �̵�
	m_fTop += y;			// �������� y��ǥ �̵�
	m_fBottom += y;		// ������ y��ǥ �̵�

	m_tPos.x = m_fLeft;
	m_tPos.y = m_fTop;
	m_tSize.x = m_fRight - m_fLeft;
	m_tSize.y = m_fBottom - m_fTop;
}
void TRect::Resize(float width, float height)
{
	float x, y;
	GetCenterPoint(x, y);	// �߽��� ��ǥ ���
	m_fLeft = x - width / 2;	// �߽����κ��� ���α����� ���ݸ�ŭ �̵�
	m_fTop = y - height / 2;	// �߽����κ��� ���α����� ���ݸ�ŭ �̵�
	m_fRight = m_fLeft + width;	// ���α��̰� width�� �ǵ��� ����
	m_fBottom = m_fTop + height;	// ���α��̰� height�� �ǵ��� ����
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
	// ���� �Ǵ� ������ ��ø�Ǿ��� �� ������ �������� �ʾҴ�. 
	// �������� �������� �ʴ� ���
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
