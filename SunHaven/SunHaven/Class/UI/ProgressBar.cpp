#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(string barTop, string barBottom, string barFill, int x, int y, int width, int height)
{
	_progressBarTop = IMAGEMANAGER->findImage(barTop);
	_progressBarFill = IMAGEMANAGER->findImage(barFill);
	_progressBarBottom = IMAGEMANAGER->findImage(barBottom);
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, width, height);
	_maxWidth = width;
	_width = _maxWidth;
	_height = height;
	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
	_rc = RectMakeCenter(_x, _y, _maxWidth, _height);
}

void ProgressBar::render(void)
{
	if (_progressBarBottom != nullptr)
	{
		_progressBarBottom->render(getMemDC(), _rc.left, _rc.top, _maxWidth, _height, 0, 0, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());
	}

	_progressBarFill->render(getMemDC(), _rc.left, _rc.top, _width, _height, 0, 0, _progressBarFill->getWidth(), _progressBarFill->getHeight());

	if (_progressBarTop != nullptr)
	{
		_progressBarTop->render(getMemDC(), _rc.left, _rc.top, _maxWidth, _height, 0, 0, _progressBarTop->getWidth(), _progressBarTop->getHeight());
	}
}

void ProgressBar::setGauge(float currentX, float maxX)
{
	_width = (currentX / maxX) * _maxWidth;
}