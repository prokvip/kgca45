#include "TDevice.h"
TDevice::TDevice() 
{

}
bool     TDevice::CreateDevice(HWND hWnd)
{
	HRESULT hr;
    m_hWnd = hWnd;

    UINT                Flags = 0;
    D3D_FEATURE_LEVEL   pFeatureLevels[] =
    {           
        D3D_FEATURE_LEVEL_11_0, // dx11 �ϵ���� ���ӵǵ���  
    };
    UINT iNumFeatureLevel = sizeof(pFeatureLevels) /
                            sizeof(pFeatureLevels[0]);

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(scd));
    scd.BufferCount = 1;
    scd.BufferDesc.Width = 800;
    scd.BufferDesc.Height = 600;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = m_hWnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    // �� ���÷���(�׷���ī��)�� DX11���� �������� ����̽� �����Ѵ�.
    hr = D3D11CreateDeviceAndSwapChain(
            nullptr,                    // �׷���ī�� ����
            D3D_DRIVER_TYPE_HARDWARE,   // �ϵ���� ����
            nullptr,                    // ��2�� �׷��ȿ����� ����� ��
            Flags,
            pFeatureLevels, 
            iNumFeatureLevel,
            D3D11_SDK_VERSION,
            &scd,
            &m_pSwapChain,
            &m_pd3dDevice,
            &m_pFeatureLevel,
            &m_pContext );
    if (FAILED(hr)) { return false;  }
    //if( SUCCEEDED( hr)) { return true }
	return true;
}
bool     TDevice::CreateRenderTargetView()
{
    //�ʱ�ȭ���� ���� 'hr' ���� ������ ����߽��ϴ�.
	HRESULT hr = S_OK;
    ID3D11Texture2D* pBackBuffer;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
    pBackBuffer->Release();
    if (FAILED(hr))
    {
        return false;
    }
    m_pContext->OMSetRenderTargets(1, &m_pRTV, NULL);
	return true;
}
void     TDevice::Render()
{
    float color[4] = { 1.0f, 0.5f, 1.0f, 1.0f };
    m_pContext->ClearRenderTargetView(m_pRTV, color);
    m_pSwapChain->Present(0, 0);
}
void     TDevice::Release()
{
    if (m_pd3dDevice)m_pd3dDevice->Release();
    if (m_pContext)m_pContext->Release();
    if (m_pSwapChain)m_pSwapChain->Release();
    if (m_pRTV)m_pRTV->Release();
}