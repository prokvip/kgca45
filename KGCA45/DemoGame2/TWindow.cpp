#include "TWindow.h"
void TestMessageBox()
{
    int iRet = MessageBox(NULL, L"처음 시작하는 윈도우",
        L"다이얼로그", MB_YESNOCANCEL);
    switch (iRet)
    {
    case IDYES: break;
    case IDNO: break;
    case IDCANCEL: break;
    case IDOK: break;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        //case WM_RBUTTONDOWN:
        //{
        //    PostQuitMessage(0);// WM_QUIT
        //}break;
    case WM_DESTROY:
        PostQuitMessage(0);// WM_QUIT
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
bool   TWindow::SetConsole()
{
    if (AllocConsole() == TRUE)
    {
        FILE* pConsoleStream = nullptr;
        if (freopen_s(&pConsoleStream, "conin$", "rt", stdin))
        {
            return false;
        }
        if (freopen_s(&pConsoleStream, "conout$", "wt", stdout))
        {
            return false;
        }
        if (freopen_s(&pConsoleStream, "conout$", "wt", stderr))
        {
            return false;
        }
        PD(L"%s %s\n",  __FUNCTIONW__,
                        L"DebugConsole START");
    }
    return true;
}
bool   TWindow::SetWindow(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    MyRegisterClass();
    if (InitInstance() == FALSE)
    {
        return false;
    }
    P(L"%s\n",L"Create Window : true");
    return true;
}
//  용도: 윈도우 클래스를 운영체제에 등록한다.
ATOM TWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon =   LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    //wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);// (COLOR_WINDOW + 1);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0,0,0));// (COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = m_szClassName.c_str();
    wcex.hIconSm = 0;

    return RegisterClassExW(&wcex);
}
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
BOOL TWindow::InitInstance()
{
    HWND hWnd = CreateWindowW(
        m_szClassName.c_str(), L"DemoGame Title",
        WS_OVERLAPPEDWINDOW,
        0, 0, 800, 600, 
        nullptr, nullptr, m_hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    m_hWnd = hWnd;
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}
bool TWindow::Run()
{
    P(L"%s\n", L"Game Running Start!");
    MSG msg;
    // 기본 메시지 루프입니다:
    //  메세지큐에 메세지 없으면 블럭된다.WM_QUIT이면 fasle반환
    //while (GetMessage(&msg, nullptr, 0, 0))
    while (1)
    {
        // 메세지큐에서 메시지를 1개 가져오고 PM_REMOVE으로 지운다.
        // 메세지큐에 메세지 없으면 false를 반환한다.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                break;
            }
        }
        else
        {
            GameRun();
        }
    }
    P(L"\n%s", L"Game Running Finish!");
    return true;
}
void  TWindow::GameRun()
{
    // 게임로직을 돌린다.(프레임)
    P(L"%s", L".");
    //Sleep(100);    
}
TWindow::~TWindow()
{
    ::UnregisterClassW(m_szClassName.c_str(), m_hInstance);
}

