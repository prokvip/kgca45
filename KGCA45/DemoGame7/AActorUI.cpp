#include "AActorUI.h"
#include "TDevice.h"
#include "URenderComponent.h"
bool     AActorUI::Create(
	TVector2 pos,
	TVector2 size,
	TString texfilepath,
	TString shaderfilepath)
{
	return m_pRenderComponent->Create(pos, size, texfilepath, shaderfilepath);
}
void   AActorUI::SetPosition(TVector2 pos)
{
	SetPosition(pos.x, pos.y);
}
void   AActorUI::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_rt.SetRect(m_Position.x, m_Position.y,
		m_Position.x + m_rt.GetWidth(),
		m_Position.y + m_rt.GetHeight());
	UpdatePositionVertexData();
}
void   AActorUI::SetRect(TVector2 pos, TVector2 size)
{
	SetRect(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
}
void   AActorUI::SetRect(float x, float y, float w, float h)
{
	m_rt.SetRect(x, y, w, h);
	m_Position = m_rt.GetPos();
	UpdatePositionVertexData();
}
void   AActorUI::Move(float x, float y)
{
	float moveX = x * g_fSPF * m_fSpeed;
	float moveY = y * g_fSPF * m_fSpeed;
	m_rt.Move(moveX, moveY);
	m_Position = m_rt.GetPos();
	UpdatePositionVertexData();
	//m_rt.Show();
}
void   AActorUI::UpdateVertexBuffer()
{
	m_pRenderComponent->UpdateVertexBuffer();
}
void   AActorUI::UpdatePositionVertexData()
{
	m_pRenderComponent->UpdatePositionVertexData();
}
void   AActorUI::UpdateColorVertexData(TColor v0, TColor v1, TColor v2, TColor v3)
{
	m_pRenderComponent->UpdateColorVertexData(v0, v1, v2, v3);
}
void   AActorUI::UpdateUVVertexData(TVector2 p, TVector2 s)
{
	m_pRenderComponent->UpdateUVVertexData(p, s);
}
void   AActorUI::Render()
{
	m_pRenderComponent->Render();
}
void   AActorUI::Tick()
{
	m_pRenderComponent->TickComponent();
}
AActorUI::AActorUI(std::wstring name) : AActor(name)
{
	m_pRenderComponent = std::make_shared<URenderComponent>(L"RenderComponent");
	if (m_pRenderComponent != nullptr)
	{
		m_pRenderComponent->SetOwner(this);
	}
}
AActorUI::AActorUI()
{
	m_pRenderComponent = std::make_shared<URenderComponent>(L"RenderComponent");
	if (m_pRenderComponent != nullptr)
	{
		m_pRenderComponent->SetOwner(this);
	}
}
AActorUI::~AActorUI()
{

}