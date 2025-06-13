#include "AActor.h"
#include "TDevice.h"
#include "URenderComponent.h"

bool     AActor::Create(
	TVector2 pos,
	TVector2 size,
	TString texfilepath,
	TString shaderfilepath)
{	
	return m_pRenderComponent->Create(pos, size, texfilepath, shaderfilepath);	
}
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
	m_Position = m_rt.GetStart();
	UpdatePositionVertexData();
}
void   AActor::Move(float x, float y)
{	
    float moveX = x * g_fSPF * m_fSpeed;
    float moveY = y * g_fSPF * m_fSpeed;
	m_rt.Move(moveX, moveY);
	m_Position = m_rt.GetStart();
	UpdatePositionVertexData();
    //m_rt.Show();
}
void   AActor::UpdateVertexBuffer()
{
	m_pRenderComponent->UpdateVertexBuffer();
}
void   AActor::UpdatePositionVertexData() 
{
	m_pRenderComponent->UpdatePositionVertexData();
}
void   AActor::UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v3) 
{
	m_pRenderComponent->UpdateColorVertexData(v0,v1,v2,v3);
}
void   AActor::UpdateUVVertexData(TVector2 p, TVector2 s) 
{
	m_pRenderComponent->UpdateUVVertexData(p,s);
}
void   AActor::Render()
{
	m_pRenderComponent->Render();
}
void   AActor::Tick()
{
	m_pRenderComponent->TickComponent();
}
AActor::AActor(std::wstring name): UObject(name)
{
	m_pRenderComponent = std::make_shared<URenderComponent>(L"RenderComponent");
	if (m_pRenderComponent != nullptr)
	{
		m_pRenderComponent->SetOwner(this);
	}
}
AActor::AActor()
{
	m_pRenderComponent = std::make_shared<URenderComponent>(L"RenderComponent");
	if (m_pRenderComponent != nullptr)
	{
		m_pRenderComponent->SetOwner(this);
	}
}
AActor::~AActor()
{
   
}