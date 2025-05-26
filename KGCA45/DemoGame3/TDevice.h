#pragma once
#include <d3d11.h>
#include <tchar.h> // _T()
//속성->링커->일반->추가종속성->d3d11.lib; dxgi.lib 추가한다.
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"d3d11.lib")


class TDevice
{	
public:
	static ID3D11Device*		m_pd3dDevice;
	static ID3D11DeviceContext*	m_pContext;
	static IDXGISwapChain*		m_pSwapChain;
	static ID3D11RenderTargetView* m_pRTV;
public:
	static void		DX_CHECK(HRESULT hr, const TCHAR* function);
	static bool     CreateDevice(HWND hWnd);
	static bool     CreateRenderTargetView();
	static void     Render();
	static void     Release();
};

