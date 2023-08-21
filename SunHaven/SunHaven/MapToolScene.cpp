#include "Stdafx.h"
#include "MapToolScene.h"

HRESULT MapToolScene::init(void)
{
	for (int i = 0; i < 100; i++)
	{
		ZeroMemory(&_tileMap, sizeof(_tileMap[0]) * 100);
	}
	memset(_tileSizeChar, '\0', sizeof(char) * sizeof(_tileSizeChar) / sizeof(_tileSizeChar[0]));
	_input = true;
	CAMERA->setPosition({ WINSIZE_X / 2, WINSIZE_Y / 2 });
	_tileMapSize = 100;
	return S_OK;
}

void MapToolScene::release(void)
{
}

void MapToolScene::update(void)
{
 CAMERA->update();
}

void MapToolScene::render(void)
{
	HPEN myPen = CreatePen(CW_DEFAULT, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	for (int i = 0; i < _tileMapSize; i++)
	{
		for (int j = 0; j < _tileMapSize; j++)
		{
			if (_tileMap[i][j]._image == nullptr)
			{
				DrawRectMake(getMemDC(), RectMakeCenter(CAMERA->worldToCameraX(j * TILEWIDTH + TILEWIDTH / 2), CAMERA->worldToCameraY(i * TILEHEIGHT + TILEHEIGHT / 2), TILEWIDTH, TILEHEIGHT));
			}
			else
			{
				_tileMap[i][j]._image->render(getMemDC(), CAMERA->worldToCameraX( j * TILEWIDTH), CAMERA->worldToCameraY( i * TILEHEIGHT));
			}
		}
	}
	SelectObject(getMemDC(), oldPen);
	DeleteObject(myPen);
	//for (int i = 0; i < _tileSize; i++)
	//{
	//	for (int j = 0; j < _tileSize; j++)
	//	{
	//		if (_tileMap[i].test(j))
	//		{
	//			//FillRect(getMemDC(), &RectMakeCenter(_tileWidth * j + _tileWidth / 2, _tileHeight * i + _tileHeight / 2, _tileWidth, _tileHeight), WHITE_BRUSH);
	//			_image->render(getMemDC(), _tileWidth * j, _tileHeight * i, _tileWidth, _tileHeight, 0, 0, _image->getWidth(), _image->getHeight());
	//		}
	//	}
	//}
	//HPEN myPen = CreatePen(CW_DEFAULT, 1, RGB(255, 255, 255));
	//HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	//for (int i = 0; i < _tileSize; i++)
	//{
	//	LineMake(getMemDC(), _tileWidth * (i + 1), 0, _tileWidth * (i + 1), _tileHeight * _tileSize);
	//}
	//for (int i = 0; i < _tileSize; i++)
	//{
	//	LineMake(getMemDC(), 0, _tileHeight * (i + 1), _tileWidth * _tileSize, _tileHeight * (i + 1));
	//}
	//SelectObject(getMemDC(), oldPen);
	//DeleteObject(myPen);
	//if (_input)
	//{
	//	HBRUSH inputBrush = CreateSolidBrush(RGB(255, 0, 255));
	//	FillRect(getMemDC(), &RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 400, 200), inputBrush);
	//	FillRect(getMemDC(), &RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 200, 50), WHITE_BRUSH);
	//	TextOut(getMemDC(), WINSIZE_X / 2 - 100, WINSIZE_Y / 2, _tileSizeChar, strlen(_tileSizeChar));
	//}
	//else
	//{
	//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _click)
	//	{
	//		_image->render(getMemDC(), _ptMouse.x - _offset.x, _ptMouse.y - _offset.y, _tileWidth, _tileHeight, 0, 0, _image->getWidth(), _image->getHeight());
	//	}
	//}
}
