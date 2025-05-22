#pragma once
#include "TStd.h"
class TWindow
{
	HINSTANCE m_hInstance;
	HWND      m_hWnd;
	std::wstring   m_szClassName= L"KGCAWindow";
public:
	bool    SetConsole();
	bool    SetWindow(HINSTANCE hInstance);
	bool    Run();
	ATOM	MyRegisterClass();
	BOOL	InitInstance();
	virtual ~TWindow();
};

