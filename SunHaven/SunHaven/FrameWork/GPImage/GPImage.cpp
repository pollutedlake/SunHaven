#include "Stdafx.h"
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

HRESULT GPImage::init(char* fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF lowColor, COLORREF highColor, Gdiplus::RotateFlipType rotateFlipType)
{
	USES_CONVERSION;

	if (_gdiInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_gdiInfo = new GDI_INFO;
	WCHAR* wstr = A2W(fileName);
	_gdiImg = Image::FromFile(wstr);

	_gdiInfo = new GDI_INFO;
	_gdiInfo->x = destX;
	_gdiInfo->y = destY;
	_gdiInfo->hMemDC = CreateCompatibleDC(hdc);
	_gdiInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _gdiImg->GetWidth(), _gdiImg->GetHeight());
	_gdiInfo->hOBit = (HBITMAP)SelectObject(_gdiInfo->hMemDC, _gdiInfo->hBit);
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

	Gdiplus::InterpolationMode imode = InterpolationModeNearestNeighbor;

	Gdiplus::ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(lowColor, highColor);

	_gdiRender = new Gdiplus::Graphics(_gdiInfo->hMemDC);

	_gdiRender->SetInterpolationMode(imode);
	_gdiRender->DrawImage
	(
		_gdiImg,
		Gdiplus::Rect
		(
			0, 0,
			_gdiInfo->width,
			_gdiInfo->height
		),
		0, 0,
		_gdiInfo->width, _gdiInfo->height,
		Gdiplus::UnitPixel, &imageAttr);

	SAFE_DELETE(_gdiRender);


	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void GPImage::release(void)
{
	if (_gdiInfo)
	{
		DeleteDC(_gdiInfo->hMemDC);
		SAFE_DELETE(_gdiImg);
		SAFE_DELETE(_gdiInfo);
	}
}


void GPImage::GPFrameRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, Gdiplus::InterpolationMode _imode, int angle)
{
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

	GdiTransparentBlt
	(
		hdc,
		destX,
		destY,
		_gdiInfo->frameWidth * wRatio,
		_gdiInfo->frameHeight * hRatio,
		_gdiInfo->hMemDC,
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth,
		_gdiInfo->frameHeight,
		RGB(0, 0, 0)
	);
}