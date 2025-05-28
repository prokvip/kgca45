#include "AActor.h"
#include "TDevice.h"
bool   AActor::SetTexture(TString filename)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(
        TDevice::m_pd3dDevice,
        filename.c_str(),
        (ID3D11Resource**)&m_pTexture,
        &m_pSRV
    );
    if (FAILED(hr))
    {
        hr = DirectX::CreateDDSTextureFromFile(
            TDevice::m_pd3dDevice,
            filename.c_str(),
            (ID3D11Resource**)&m_pTexture,
            &m_pSRV
        );
        if (FAILED(hr))
        {
            return false;
        }
    }
    m_pTexture->GetDesc(&m_TexDesc);
    return true;
}
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
    UpdateVertexBuffer();
}
void   AActor::SetRect(TPoint pos, TPoint size)
{		
	SetRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
}
void   AActor::SetRect(float x, float y, float w, float h)
{	
	m_rt.SetRect(x, y, w, h); 
	m_Position = m_rt.GetPos();
    UpdateVertexBuffer();
}
void   AActor::Move(float x, float y)
{	
    float moveX = x * g_fSPF * m_fSpeed;
    float moveY = y * g_fSPF * m_fSpeed;
	m_rt.Move(moveX, moveY);
	m_Position = m_rt.GetPos();
    UpdateVertexBuffer();
    //m_rt.Show();
}
void   AActor::UpdateVertexBuffer()
{
}
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
    if (m_pTexture) m_pTexture->Release();
    if (m_pSRV) m_pSRV->Release();
}