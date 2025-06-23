#include "AActor.h"
#include "TDevice.h"
#include "URenderComponent.h"

bool     AActor::Create(
	TVector2 pos,
	TVector2 size,
	TString texfilepath,
	TString shaderfilepath)
{	
	m_pInitPos = pos;
	m_pInitSize = size;
	return m_pRenderComponent->Create(pos, size, texfilepath, shaderfilepath);	
}
bool     AActor::Create(
	TVector2 pos,
	TVector2 size,
	TString texfilepath,
	TString texMaskfilepath,
	TString shaderfilepath)
{
	return m_pRenderComponent->Create(pos, size, 
		texfilepath, texMaskfilepath, shaderfilepath);
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
void   AActor::Transform()
{
	//m_fAngle = g_fGameTimer;
	//m_vScale = TVector2(cosf(g_fGameTimer), cosf(g_fGameTimer));
	
	TRect  rt = GetRect();
	auto center = rt.GetCenter();
	// 원점으로 이동 변환(transform)
	m_matOriginTrans.Translaton(-center.x, -center.y);
	// 원점에서 회전 변환(transform)
	m_matRotation.Rotation(m_fAngle);
	// 원위치로 이동 변환(transform)
	m_matTrans.Translaton(center.x, center.y);
	m_matScale.Scale(m_vScale.x, m_vScale.y);
	// 결합행렬
	m_matWorld = m_matOriginTrans * m_matScale *
		m_matRotation * m_matTrans;
	std::vector<TVertex> list(m_pRenderComponent->m_InitVertexList.size());
	for (size_t i = 0; i < m_pRenderComponent->m_InitVertexList.size(); ++i)
	{
		list[i].p = m_pRenderComponent->m_InitVertexList[i].p * m_matWorld;
	}
	// 원점에서 회전 변환된 정점을 복사한다.
	for (size_t i = 0; i < m_pRenderComponent->m_VertexList.size(); ++i)
	{
		m_pRenderComponent->m_VertexList[i].p = list[i].p;
	}
	//// 원점으로 이동 변환(transform)
	//TRect  rt = GetOwner()->GetRect();
	//auto center = rt.GetCenter();
	//TMatrix matOriginTrans, matRotation, matTrans;
	//matOriginTrans.Translaton(-center.x, -center.y);
	//std::vector<TVertex> list(m_InitVertexList.size());
	//for (size_t i = 0; i < m_InitVertexList.size(); ++i)
	//{
	//	list[i].p = m_InitVertexList[i].p * matOriginTrans;
	//}
	//// 원점에서 회전 변환(transform)
	//matRotation.Rotation(g_fGameTimer);
	//for (size_t i = 0; i < m_InitVertexList.size(); ++i)
	//{
	//	list[i].p = list[i].p * matRotation;
	//}
	//matTrans.Translaton(center.x, center.y);
	//for (size_t i = 0; i < m_InitVertexList.size(); ++i)
	//{
	//	list[i].p = list[i].p * matTrans;
	//}
	//// 원점에서 회전 변환된 정점을 복사한다.
	//for (size_t i = 0; i < m_VertexList.size(); ++i)
	//{
	//	m_VertexList[i].p = list[i].p;
	//}
	//UpdateVertexBuffer();
}
void   AActor::UpdatePositionVertexData() 
{
	m_pRenderComponent->UpdatePositionVertexData();
	for (int i = 0; i < m_pRenderComponent->m_InitVertexList.size(); i++)
	{
		m_pRenderComponent->m_InitVertexList[i].p =
			m_pRenderComponent->m_VertexList[i].p;
	}
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