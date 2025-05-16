#include "AActor.h"
void   AActor::SetPosition(TPoint pos)
{
	m_Position = pos;
}
void   AActor::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}
void   AActor::SetRect(TPoint pos, TPoint size)
{	
	m_rt.SetRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
}
void   AActor::SetRect(float x, float y, float w, float h)
{
	m_rt.SetRect(x, y, w, h);
}
void   AActor::Move(float x, float y)
{
	m_rt.Move(x, y);
}
void   AActor::Show()
{
	m_rt.Show();
}
void   AActor::Tick()
{
	std::wcout << GetName() << std::endl;
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