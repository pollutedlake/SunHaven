#include "Stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init(void)
{
    _timer = new Timer;
    _timer->init();
    return S_OK;
}

void TimeManager::release(void)
{
    if (_timer != nullptr)
    {
        SAFE_DELETE(_timer);
        _timer = nullptr;
    }
}

void TimeManager::update(float lock)
{
    if (_timer != nullptr)
    {
        _timer->tick(lock);
    }
}

void TimeManager::render(HDC hdc)
{
    char str[256];

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
    if (_timer != nullptr)
    {
        sprintf_s(str, "FPS: %d", _timer->getFrameRate());
        TextOut(hdc, 0, 0, str, strlen(str));
    }
#else  // !_DEBUG
    if (_timer != nullptr)
    {
        sprintf_s(str, "FPS: %d", _timer->getFrameRate());
        TextOut(hdc, 0, 0, str, strlen(str));
    }
#endif
}

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}
