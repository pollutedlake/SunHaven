#include "Stdafx.h"

#include "MainGame.h"
MainGame* _mg;

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int, int, int, int);

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdParam,
    int       nCmdShow)
{

    _mg = new MainGame();

    _hInstance = hInstance;

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                              
    wndClass.cbWndExtra = 0;                                              
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);         
    wndClass.hCursor = LoadCursor(NULL, IDC_CROSS);                       
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                     
    wndClass.hInstance = hInstance;                                       
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                              
    wndClass.lpszClassName = WINNAME;                                     
    wndClass.lpszMenuName = NULL;                                         
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                             

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME,           
        WINNAME,           
        WINSTYLE,          
        WINSTART_X,        
        WINSTART_Y,        
        MYWINSIZE_X,       
        MYWINSIZE_Y,       
        NULL,              
        (HMENU)NULL,       
        hInstance,         
        NULL               
                           
    );

    setWindowSize(WINSTART_X, WINSTART_Y, MYWINSIZE_X, MYWINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);
    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;

    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) break;
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            TIMEMANAGER->update(60.0f);
            _mg->update();
            _mg->render();
        }
    }

    GdiplusShutdown(gdiplusToken);

    _mg->release();
    UnregisterClass(WINNAME, hInstance);

    return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}