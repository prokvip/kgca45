#include "AActor.h"
#include "TDevice.h"

void   AActor::SetPosition(TVector2 pos)
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
	UpdatePositionVertexData();
}
void   AActor::SetRect(TVector2 pos, TVector2 size)
{		
	SetRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
}
void   AActor::SetRect(float x, float y, float w, float h)
{	
	m_rt.SetRect(x, y, w, h); 
	m_Position = m_rt.GetPos();
	UpdatePositionVertexData();
}
void   AActor::Move(float x, float y)
{	
    float moveX = x * g_fSPF * m_fSpeed;
    float moveY = y * g_fSPF * m_fSpeed;
	m_rt.Move(moveX, moveY);
	m_Position = m_rt.GetPos();
	UpdatePositionVertexData();
    //m_rt.Show();
}
void   AActor::UpdateVertexBuffer(){}
void   AActor::UpdatePositionVertexData() {}
void   AActor::UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v3) {}
void   AActor::UpdateUVVertexData(TVector2 p, TVector2 s) {}
void   AActor::Render()
{
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