#pragma once
#include "TStd.h"
class TWindow
{
	bool			m_bActive = false;
	HINSTANCE		m_hInstance;
	HWND			m_hWnd;
	std::wstring	m_szClassName= L"KGCAWindow";
public:
	bool    SetConsole();
	bool    SetWindow(HINSTANCE hInstance);
	bool    Run();
	ATOM	MyRegisterClass();
	BOOL	InitInstance();
public:
	virtual void GameRun();
	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	TWindow();
	virtual ~TWindow();
};

