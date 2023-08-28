#include "stdafx.h"
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

    /*
    - 릴리즈가 아닌 디버그 모드 일때 실행이 된다.
    ㄴ 테스트 용도가 강하다. (개발)

    - 그렇기 때문에 일반적으로 유저가 접하면 안되는 정보를 확인하면서 개발할때 유효
    ㄴ 좀더 확실한 예외가 필요하다면 어썰트를 이용해서 예외 처리한다.
    */

#ifdef _DEBUG
    if (_timer != nullptr)
    {
        sprintf_s(str, "FPS: %d", _timer->getFrameRate());
        TextOut(hdc, 0, 0, str, strlen(str));

        sprintf_s(str, "WorldTime: %f", _timer->getWorldTime());
        TextOut(hdc, 0, 20, str, strlen(str));

        sprintf_s(str, "ElapsedTime: %f", _timer->getElapsedTime());
        TextOut(hdc, 0, 40, str, strlen(str));
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
