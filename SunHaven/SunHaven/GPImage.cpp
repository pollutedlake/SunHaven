#include "stdafx.h"
#include "GPImage.h"

GPImage::GPImage() : _gdiInfo(nullptr),
_fileName(nullptr),
_isTrans(false),
_transColor(RGB(0, 0, 0))
{

}

GPImage::~GPImage()
{
}

HRESULT GPImage::init(char* fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color, Gdiplus::RotateFlipType rotateFlipType)
{
	USES_CONVERSION;

	if (_gdiInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_gdiInfo = new GDI_INFO;
	WCHAR* wstr = A2W(fileName);
	_gdiImg = new Gdiplus::Image(wstr);

	_gdiInfo = new GDI_INFO;
	_gdiInfo->x = destX;
	_gdiInfo->y = destY;
	_gdiInfo->width = _gdiImg->GetWidth();
	_gdiInfo->height = _gdiImg->GetHeight();
	_gdiInfo->currentFrameX = 0;
	_gdiInfo->currentFrameY = 0;
	_gdiInfo->maxFrameX = maxFrameX - 1;
	_gdiInfo->maxFrameY = maxFrameY - 1;
	_gdiInfo->frameWidth = _gdiImg->GetWidth() / maxFrameX;
	_gdiInfo->frameHeight = _gdiImg->GetHeight() / maxFrameY;
	_gdiImg->RotateFlip(rotateFlipType);

	_isTrans = isTrans;
	_transColor = color;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void GPImage::release(void)
{
	if (_gdiInfo)
	{
		DeleteDC(_gdiInfo->hMemDC);
		SAFE_DELETE(_gdiInfo);
		SAFE_DELETE(_gdiImg);
	}
}


void GPImage::GPFrameRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, Gdiplus::InterpolationMode _imode, int angle)
{
	Gdiplus::InterpolationMode imode = _imode;	// 보간 모드


	_gdiInfo->currentFrameX = currentFrameX;
	_gdiInfo->currentFrameY = currentFrameY;

	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}

	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}


	Gdiplus::ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Gdiplus::Graphics(hdc);

	Gdiplus::Graphics graphics(hdc);

	Gdiplus::Matrix mat;
	mat.RotateAt(angle, Gdiplus::PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->SetInterpolationMode(imode);
	_gdiRender->DrawImage
	(
		_gdiImg,
		Gdiplus::Rect
		(
			destX,
			destY,
			_gdiInfo->frameWidth * wRatio,
			_gdiInfo->frameHeight * hRatio
		),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		Gdiplus::UnitPixel, &imageAttr);

	SAFE_DELETE(_gdiRender);
}