#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_progressBarTop = IMAGEMANAGER->findImage("ProgressBarTop");
	_progressBarFill = IMAGEMANAGER->findImage("ProgressBarFill");
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, width, height);
	_width = _progressBarFill->getWidth() * 1.5;
	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
	_rc = RectMakeCenter(_x, _y, _progressBarFill->getWidth() * 1.5, _progressBarFill->getHeight() * 1.5);
}

void ProgressBar::render(void)
{
	_progressBarFill->render(getMemDC(), _rc.left, _rc.top, _width, _progressBarFill->getHeight() * 1.5, 0, 0, _progressBarFill->getWidth(), _progressBarFill->getHeight());
	_progressBarTop->render(getMemDC(),	_rc.left, _rc.top, _progressBarFill->getWidth() * 1.5, _progressBarFill->getHeight() * 1.5, 
		0, 0, _progressBarTop->getWidth(), _progressBarTop->getHeight());
}

void ProgressBar::setGauge(float currentX, float maxX)
{
	_width = (currentX / maxX) * _progressBarFill->getWidth() * 1.5;
}