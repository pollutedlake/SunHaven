#pragma once
#include <locale>
#include <codecvt>
#include <GdiPlus.h>
#include <atlconv.h>

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

class GPImage
{
public:

	typedef struct tagImage
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP	hBit;
		HBITMAP	hOBit;
		BYTE	loadType;
		float	x;
		float	y;
		int		width;
		int		height;
		int		currentFrameX;
		int		currentFrameY;
		int		maxFrameX;
		int		maxFrameY;
		int		frameWidth;
		int		frameHeight;

		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}

	} GDI_INFO, * LPGDI_INFO;

private:
	LPGDI_INFO				_gdiInfo;

	Gdiplus::Graphics* _gdi;
	Gdiplus::Graphics* _gdiRender;
	Gdiplus::Image* _gdiImg;

	char* _fileName;
	bool					_isTrans;
	COLORREF				_transColor;
public:
	HRESULT init(char* fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF lowColor, COLORREF highColor, Gdiplus::RotateFlipType rotateFlipType = Gdiplus::RotateNoneFlipNone);
	void release(void);
	void GPFrameRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, Gdiplus::InterpolationMode _imode, int angle = 0);

	inline int getWidth(void) { return _gdiInfo->width; }
	inline int getHeight(void) { return _gdiInfo->height; }

	inline int getFrameX(void)
	{
		if (_gdiInfo != nullptr)
		{
			return _gdiInfo->currentFrameX;
		}
	}
	inline void setFrameX(int frameX)
	{
		if (_gdiInfo != nullptr)
		{
			_gdiInfo->currentFrameX = frameX;

			if (frameX > _gdiInfo->maxFrameX)
			{
				_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
			}
		}

	}

	inline int getFrameY(void)
	{
		if (_gdiInfo != nullptr)
		{
			return _gdiInfo->currentFrameY;
		}
	}
	inline void setFrameY(int frameY)
	{
		if (_gdiInfo != nullptr)
		{
			_gdiInfo->currentFrameY = frameY;

			if (frameY > _gdiInfo->maxFrameY)
			{
				_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
			}
		}

	}

	inline int getFrameWidth(void) { return _gdiInfo->frameWidth; }
	inline int getFrameHeight(void) { return _gdiInfo->frameHeight; }

	inline int getMaxFrameX(void) { return _gdiInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _gdiInfo->maxFrameY; }

	GPImage();
	~GPImage();
};