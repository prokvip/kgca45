#include "TDevice.h"
#include "TStd.h"

ID3D11Device* TDevice::m_pd3dDevice = nullptr;
ID3D11DeviceContext* TDevice::m_pContext = nullptr;
IDXGISwapChain* TDevice::m_pSwapChain = nullptr;
ID3D11RenderTargetView* TDevice::m_pRTV = nullptr;
D3D11_VIEWPORT		TDevice::m_ViewPort = {0,};

void TDevice::DX_CHECK(HRESULT hr, const TCHAR* function)
{
    if (FAILED(hr))
    {
        LPWSTR output;
        WCHAR buffer[256] = { 0, };
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&output, 0, NULL);
        wsprintf(buffer, L"File=%ls\nLine=%d\nFuction=%ls", _T(__FILE__), __LINE__, function);
        //MessageBox(NULL, buffer, output, MB_OK);

        P(L"%s:%s\n", buffer, output);
    }
}
bool     TDevice::CreateDevice(HWND hWnd)
{
	HRESULT hr;
    UINT                Flags = 0;
    D3D_FEATURE_LEVEL   pFeatureLevels[] =
    {           
        D3D_FEATURE_LEVEL_11_0, // dx11 하드웨어 가속되도록  
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
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    // 주 디스플레이(그래픽카드)의 DX11가속 버전으로 디바이스 생성한다.
    hr = D3D11CreateDeviceAndSwapChain(
            nullptr,                    // 그래픽카드 선택
            D3D_DRIVER_TYPE_HARDWARE,   // 하드웨어 가속
            nullptr,                    // 제2의 그래픽엔진을 사용할 때
            Flags,
            pFeatureLevels, 
            iNumFeatureLevel,
            D3D11_SDK_VERSION,
            &scd,
            &m_pSwapChain,
            &m_pd3dDevice,
            nullptr,
            &m_pContext );
    if (FAILED(hr)) { return false;  }
    //if( SUCCEEDED( hr)) { return true }
	return true;
}
bool     TDevice::CreateRenderTargetView()
{
    //초기화되지 않은 'hr' 지역 변수를 사용했습니다.
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
void TDevice::SetViewPort()
{
    DXGI_SWAP_CHAIN_DESC Desc;
    m_pSwapChain->GetDesc(&Desc);
    // Setup the viewport    
    m_ViewPort.Width = Desc.BufferDesc.Width;
    m_ViewPort.Height = Desc.BufferDesc.Height;
    m_ViewPort.MinDepth = 0.0f;
    m_ViewPort.MaxDepth = 1.0f;
    m_ViewPort.TopLeftX = 0;
    m_ViewPort.TopLeftY = 0;
    m_pContext->RSSetViewports(1, &m_ViewPort);
}
void     TDevice::PreRender()
{
    float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    m_pContext->ClearRenderTargetView(m_pRTV, color);
   
}
void     TDevice::PostRender()
{
    m_pSwapChain->Present(0, 0);
}
void     TDevice::Release()
{
    if (m_pd3dDevice)m_pd3dDevice->Release();
    if (m_pContext)m_pContext->Release();
    if (m_pSwapChain)m_pSwapChain->Release();
    if (m_pRTV)m_pRTV->Release();
}