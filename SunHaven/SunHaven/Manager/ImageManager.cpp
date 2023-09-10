#include "Stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
	return S_OK;
}

void ImageManager::release(void)
{
	deleteAll();
}

GImage* ImageManager::addImage(string strKey, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		cout << strKey << endl;
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	GImage* img = findImage(strKey);
	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}
	_mImageList.insert(make_pair(strKey, img));
	return img;
}

GPImage* ImageManager::addGPFrameImage(string strKey, char* fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color, Gdiplus::RotateFlipType rotateFlipType)
{
	GPImage* img = findGPImage(strKey);

	if (img) return img;

	img = new GPImage;

	if (FAILED(img->init(fileName, destX, destY, maxFrameX, maxFrameY, isTrans, color, rotateFlipType)))
	{
		cout << strKey << endl;
		SAFE_DELETE(img);

		return NULL;
	}

	_mGPImageList.insert(make_pair(strKey, img));

	return nullptr;
}

GImage* ImageManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}
	return nullptr;
}

GPImage* ImageManager::findGPImage(string strKey)
{
	auto key = _mGPImageList.find(strKey);

	// 검색한 키를 찾은 경우
	if (key != _mGPImageList.end())
	{
		return key->second;
	}

	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);
		return true;
	}
	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();
	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mImageList.clear();
	mapGPImageIter GPiter = _mGPImageList.begin();
	for (; GPiter != _mGPImageList.end();)
	{
		if (GPiter->second != NULL)
		{
			GPiter->second->release();
			SAFE_DELETE(GPiter->second);
			GPiter = _mGPImageList.erase(GPiter);
		}
		else
		{
			++GPiter;
		}
	}
	_mGPImageList.clear();
	return true;
}

void ImageManager::render(string strKey, HDC hdc)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight, alpha);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int destWidth, int destHeight, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, destWidth, destHeight, currentFrameX, currentFrameY);
}

void ImageManager::GPFrameRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, Gdiplus::InterpolationMode _imode, int angle)
{
	GPImage* img = findGPImage(strKey);

	if (img) img->GPFrameRender(hdc, destX, destY, wRatio, hRatio, currentFrameX, currentFrameY, _imode, angle);
}

void ImageManager::GPRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int sourX, int sourY, int sourWidth, int sourHeight, Gdiplus::InterpolationMode _imode, int angle)
{
	GPImage* img = findGPImage(strKey);

	if (img) img->GPRender(hdc, destX, destY, wRatio, hRatio, sourX, sourY, sourWidth, sourHeight, _imode, angle);
}

void ImageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

