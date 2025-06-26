#pragma once
#pragma comment (lib, "DirectXTK.lib")
#pragma comment (lib, "TGameCore.lib")
#include <Windows.h>
#include <iostream>
#include <conio.h>//getch
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory> // smart point
#include <wrl.h> 
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include "TRect.h"
#include <atlconv.h> // A2W

using namespace Microsoft::WRL;
using namespace std;
using TString = std::wstring;

struct TColor
{
	float  r;
	float  g;
	float  b;
	float  a;
	TColor() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	TColor(float r, float g, float b, float a)
	{
		this->r = r; this->g = g; this->b = b; this->a = a;
	}
};

struct TVertex
{
	TVector2 p;
	TColor c;
	TVector2 t;
	TVertex() : p{ 0,0 }, c{ 1.0f,1.0f,1.0f,1.0f }, t{ 0.0f,0.0f } {}
	TVertex(TVector2 p1, TColor c1, TVector2 t1) : p(p1), c(c1), t(t1) {}
	TVertex(float x, float y, float r, float g, float b, float a, float u, float v)
	{
		p.x = x; p.y = y;
		c.r = r; c.g = g; c.b = b; c.a = a;
		t.x = u; t.y = v;
	}
};
extern HWND   g_hWnd;
extern float g_fSPF;
extern float g_fGameTimer;
static void ConsolePrintW(const wchar_t* fmt, ...)
{
	va_list ap;
	wchar_t buf[MAX_PATH];

	va_start(ap, fmt);
	vswprintf_s(buf, fmt, ap);
	va_end(ap);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWriten;
	WriteConsoleW(handle, buf, (DWORD)wcslen(buf), &dwBytesWriten, 0);
}

static void ConsolePrintA(const char* fmt, ...)
{
	va_list ap;
	char buf[MAX_PATH];

	va_start(ap, fmt);
	vsprintf_s(buf, fmt, ap);
	va_end(ap);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWriten;
	WriteConsoleA(handle, buf, (DWORD)strlen(buf), &dwBytesWriten, 0);
}
static std::wstring to_mw(const std::string& _src)
{
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
	USES_CONVERSION;
	return std::string(W2A(_src.c_str()));
};
#define PrintA(fmt,...)         ConsolePrintA( fmt, __VA_ARGS__ )
#define PrintDetailA(fmt,...)   ConsolePrintA( "[%s %d] : " fmt, __FILE__,__LINE__, ##__VA_ARGS__ )
#define P(fmt,...)    ConsolePrintW( fmt, __VA_ARGS__ )
#define PD(fmt,...)   ConsolePrintW( L"[%s %d] : " fmt, __FILEW__,__LINE__, ##__VA_ARGS__ )



#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPWSTR    lpCmdLine,int       nCmdShow) {
#define GAME_RUN Sample win;if (win.SetWindow(hInstance)){return win.Run();}   return 1;
#define GAME_END }
#define TGAME GAME_START;GAME_RUN;GAME_END;