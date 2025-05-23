#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>//getch

using namespace std;

static void ConsolePrintW(const wchar_t* fmt, ...)
{
	va_list ap;
	wchar_t buf[MAX_PATH];

	va_start(ap, fmt);
	vswprintf_s(buf, fmt, ap);
	va_end(ap);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWriten;
	WriteConsoleW(handle, buf, wcslen(buf), &dwBytesWriten, 0);
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
	WriteConsoleA(handle, buf, strlen(buf), &dwBytesWriten, 0);
}

#define PrintA(fmt,...)         ConsolePrintA( fmt, __VA_ARGS__ )
#define PrintDetailA(fmt,...)   ConsolePrintA( "[%s %d] : " fmt, __FILE__,__LINE__, ##__VA_ARGS__ )
#define P(fmt,...)    ConsolePrintW( fmt, __VA_ARGS__ )
#define PD(fmt,...)   ConsolePrintW( L"[%s %d] : " fmt, __FILEW__,__LINE__, ##__VA_ARGS__ )



#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPWSTR    lpCmdLine,int       nCmdShow) {
#define GAME_RUN Sample win;if (win.SetWindow(hInstance)){return win.Run();}   return 1;
#define GAME_END }
#define TGAME GAME_START;GAME_RUN;GAME_END;