#pragma once
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <dxgidebug.h>
#include <tchar.h> // _T()
//�Ӽ�->��Ŀ->�Ϲ�->�߰����Ӽ�->d3d11.lib; dxgi.lib �߰��Ѵ�.
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"d3d11.lib")
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

class TDevice
{	
public:
	static ID3D11Device*		m_pd3dDevice;
	static ID3D11DeviceContext*	m_pContext;
	static IDXGISwapChain*		m_pSwapChain;
	static ID3D11RenderTargetView* m_pRTV;
	static D3D11_VIEWPORT		m_ViewPort;			// ����Ʈ 
public:
	static void		DX_CHECK(HRESULT hr, const TCHAR* function);
	static bool     CreateDevice(HWND hWnd);
	static bool     CreateRenderTargetView();
	static void		SetViewPort();
	static void     PreRender();
	static void     PostRender();
	static void     Release();
};

