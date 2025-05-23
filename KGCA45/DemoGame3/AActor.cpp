#include "AActor.h"
void   AActor::SetPosition(TPoint pos)
{
	SetPosition(pos.x, pos.y);
}
void   AActor::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_rt.SetRect(m_Position.x, m_Position.y, 
		m_Position.x + m_rt.GetWidth(),
		m_Position.y + m_rt.GetHeight());
}
void   AActor::SetRect(TPoint pos, TPoint size)
{		
	SetRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
}
void   AActor::SetRect(float x, float y, float w, float h)
{	
	m_rt.SetRect(x, y, w, h); 
	m_Position = m_rt.GetPos();
}
void   AActor::Move(float x, float y)
{	
	m_rt.Move(x, y);
	m_Position = m_rt.GetPos();
}
void   AActor::Show()
{
	m_rt.Show();
}
void   AActor::Tick()
{
}
AActor::AActor(std::wstring name): UObject(name)
{

}
AActor::AActor()
{

}
AActor::~AActor()
{

}