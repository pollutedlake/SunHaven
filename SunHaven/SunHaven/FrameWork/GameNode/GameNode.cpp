#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
    return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;

    if (managerInit)
    {
        setlocale(LC_ALL, "korean");

        CAMERA->init();
        KEYMANAGER->init();
        RND->init();
        IMAGEMANAGER->init();
        SOUNDMANAGER->init();
        SCENEMANAGER->init();
        TIMEMANAGER->init();
        INIDATAMANAGER->init();
        JSONDATAMANAGER->init();
        DATAMANAGER->init();
    }

    return S_OK;
}

void GameNode::release(void)
{
    if (_managerInit)
    {
        KillTimer(_hWnd, 1);
        RND->releaseSingleton();
        KEYMANAGER->releaseSingleton();
        IMAGEMANAGER->release();
        IMAGEMANAGER->releaseSingleton();
        SOUNDMANAGER->releaseSingleton();
        TIMEMANAGER->release();
        TIMEMANAGER->releaseSingleton();
        INIDATAMANAGER->release();
        INIDATAMANAGER->releaseSingleton();
        JSONDATAMANAGER->release();
        JSONDATAMANAGER->releaseSingleton();
        DATAMANAGER->release();
        DATAMANAGER->releaseSingleton();
        CAMERA->release();
        CAMERA->releaseSingleton();
    }

    ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
}

void GameNode::render()
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        this->render();
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;
    case WM_DESTROY:             
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
