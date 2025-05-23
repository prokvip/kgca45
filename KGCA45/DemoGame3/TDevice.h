#pragma once
#include <d3d11.h>
//�Ӽ�->��Ŀ->�Ϲ�->�߰����Ӽ�->d3d11.lib; dxgi.lib �߰��Ѵ�.
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"d3d11.lib")
class TDevice
{
	HWND					m_hWnd;
	D3D_FEATURE_LEVEL		m_pFeatureLevel;
public:
	ID3D11Device*			m_pd3dDevice = nullptr;
	ID3D11DeviceContext*	m_pContext = nullptr;	
	IDXGISwapChain*			m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;
public:
	bool     CreateDevice(HWND hWnd);
	bool     CreateRenderTargetView();
	void     Render();
	void     Release();
	TDevice();
};

