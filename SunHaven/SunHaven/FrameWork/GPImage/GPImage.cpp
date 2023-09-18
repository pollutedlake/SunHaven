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

HRESULT GPImage::init(char* fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color, Gdiplus::RotateFlipType rotateFlipType)
{
	USES_CONVERSION;

	if (_gdiInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_gdiInfo = new GDI_INFO;
	WCHAR* wstr = A2W(fileName);
	_gdiImg = new Bitmap(wstr);

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

	Gdiplus::InterpolationMode imode = InterpolationModeNearestNeighbor;

	Gdiplus::ImageAttributes imageAttr;

	

	_gdiRender = new Gdiplus::Graphics(hdc);

	_gdiRender->SetInterpolationMode(imode);
	Gdiplus::Matrix mat;
	mat.RotateAt(angle, Gdiplus::PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);
	_gdiRender->DrawImage
	(
		_gdiImg,
		Gdiplus::Rect
		(
			destX, destY,
			_gdiInfo->frameWidth * wRatio,
			_gdiInfo->frameHeight * hRatio
		),
		_gdiInfo->frameWidth * currentFrameX, _gdiInfo->frameHeight * currentFrameY,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		Gdiplus::UnitPixel, &imageAttr);

	SAFE_DELETE(_gdiRender);
}

void GPImage::GPRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int sourX, int sourY, int sourWith, int sourHeight, Gdiplus::InterpolationMode _imode, int angle)
{

	Gdiplus::InterpolationMode imode = InterpolationModeNearestNeighbor;

	Gdiplus::ImageAttributes imageAttr;



	_gdiRender = new Gdiplus::Graphics(hdc);

	_gdiRender->SetInterpolationMode(imode);
	Gdiplus::Matrix mat;
	mat.RotateAt(angle, Gdiplus::PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);
	_gdiRender->DrawImage
	(
		_gdiImg,
		Gdiplus::Rect
		(
			destX, destY,
			sourWith * wRatio,
			sourHeight * hRatio
		),
		sourX, sourY,
		sourWith, sourHeight,
		Gdiplus::UnitPixel, &imageAttr);

	SAFE_DELETE(_gdiRender);
}

void GPImage::GPRotateRender(HDC hdc, int destX, int destY, int rotateCenterX, int rotateCenterY, float wRatio, float hRatio, int sourX, int sourY, int sourWith, int sourHeight, Gdiplus::InterpolationMode _imode, int angle)
{
	Gdiplus::InterpolationMode imode = InterpolationModeNearestNeighbor;

	Gdiplus::ImageAttributes imageAttr;



	_gdiRender = new Gdiplus::Graphics(hdc);

	_gdiRender->SetInterpolationMode(imode);
	Gdiplus::Matrix mat;
	mat.RotateAt(angle, Gdiplus::PointF(float(rotateCenterX), float(rotateCenterY)));
	_gdiRender->SetTransform(&mat);
	_gdiRender->DrawImage
	(
		_gdiImg,
		Gdiplus::Rect
		(
			destX, destY,
			sourWith * wRatio,
			sourHeight * hRatio
		),
		sourX, sourY,
		sourWith, sourHeight,
		Gdiplus::UnitPixel, &imageAttr);

	SAFE_DELETE(_gdiRender);
}
