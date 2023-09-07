#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_progressBarBottom = IMAGEMANAGER->findGPImage("ProgressBarBottom");
	_progressBarTop = IMAGEMANAGER->findGPImage("ProgressBarBottom");
	_progressBarFill = IMAGEMANAGER->findImage("ProgressBarFill");
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, width, height);
	_width = _progressBarBottom->getWidth();
	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
	_rc = RectMakeCenter(_x, _y, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());
}

void ProgressBar::render(void)
{
	_progressBarBottom->GPFrameRender(getMemDC(),
		_rc.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2,
		1.0f, 1.0f,
		0, 0,
		InterpolationModeNearestNeighbor, 0);
	_progressBarFill->render(getMemDC(),
		_rc.left + _progressBarFill->getWidth() / 2,
		_y + _progressBarFill->getHeight() / 2,
		0, 0,
		_width,
		_progressBarFill->getHeight());
	_progressBarTop->GPFrameRender(getMemDC(),
		_rc.left + _progressBarTop->getWidth() / 2,
		_y + _progressBarTop->getHeight() / 2,
		1.0f, 1.0f,
		0, 0,
		InterpolationModeNearestNeighbor, 0);
}

void ProgressBar::setGauge(float currentX, float maxX)
{
	_width = (currentX / maxX) * _progressBarBottom->getWidth();
}