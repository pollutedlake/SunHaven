#pragma once
#include "../FrameWork/SingletonBase/SingletonBase.h"
#include "../FrameWork/GImage/GImage.h"
#include "../FrameWork/GPImage/GPImage.h"

class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, GImage*> mapImageList;
	typedef map<string, GImage*> ::iterator mapImageIter;

	typedef map<string, GPImage*> mapGPImageList;
	typedef map<string, GPImage*>::iterator mapGPImageIter;

	mapImageList _mImageList;
	mapGPImageList _mGPImageList;

public:
	HRESULT init(void);
	void release(void);

	GImage* addImage(string strKey, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GPImage* addGPFrameImage(string strKey, char* fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color, Gdiplus::RotateFlipType rotateFlipType);

	GImage* findImage(string strKey);
	GPImage* findGPImage(string strKey);

	bool deleteImage(string strKey);
	bool deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void render(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY);
	void GPFrameRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, Gdiplus::InterpolationMode _imode, int angle);
	void GPRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int sourX, int sourY, int sourWidth, int sourHeight,  Gdiplus::InterpolationMode _imode, int angle);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	ImageManager() {}
	~ImageManager() {}
};

