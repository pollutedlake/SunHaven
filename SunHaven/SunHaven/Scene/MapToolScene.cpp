// 박상현
#include "Stdafx.h"
#include "MapToolScene.h"

HRESULT MapToolScene::init(void)
{
	for (int i = 0; i < 100; i++)
	{
		ZeroMemory(&_tileMap, sizeof(_tileMap[0]) * 100);
	}
	for (int i = 0; i < 10; i++)
	{
		ZeroMemory(&_tileMap, sizeof(_tileMap[0]) * 10);
	}
	for (int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			char _tileName[64];
			wsprintf(_tileName, "Tile%d", i * 10 + (j + 1));
			_tiles[i][j]._image = IMAGEMANAGER->findImage(_tileName);
			_tiles[i][j]._tile = 10 * i + j + 1;
		}
	}
	memset(_tileSizeChar, '\0', sizeof(char) * sizeof(_tileSizeChar) / sizeof(_tileSizeChar[0]));
	_input = true;
	_tileMapBuffer = IMAGEMANAGER->addImage("TileMapBuffer", MapToolWidth, MapToolHeight);
	_tilesBuffer = IMAGEMANAGER->addImage("TilesBuffer", TILEWIDTH * 10, TILEHEIGHT  * 10);
	CAMERA->init();
	CAMERA->setPosition({ WINSIZE_X / 2, WINSIZE_Y / 2 });
	_tileMapSize = 100;
	CAMERA->setLimitRight(_tileMapSize * TILEWIDTH - MapToolWidth / 2);
	CAMERA->setLimitBottom(_tileMapSize * TILEHEIGHT - MapToolHeight / 2);
	_cameraPos = { MapToolWidth / 2, MapToolHeight  / 2};
	_layer = 0;
	return S_OK;
}

void MapToolScene::release(void)
{
}

void MapToolScene::update(void)
{
	CAMERA->update();
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_cameraPos.y -= 10;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cameraPos.y += 10;

	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cameraPos.x -= 10;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cameraPos.x += 10;
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x > 900 && _ptMouse.x < 900 + 240)
		{
			_selectTile = _tiles[(_ptMouse.y - 50) / TILEHEIGHT][(_ptMouse.x - 900) / TILEWIDTH];
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x > 50 && _ptMouse.x < MapToolWidth + 50)
		{
			_tileMap[_layer][(_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) / TILEHEIGHT][(_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) / TILEWIDTH] = _selectTile;
			cout << (_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) / TILEWIDTH << "\t" << (_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) / TILEHEIGHT << endl;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('s'))
	{
		fopen_s(&_fp, "FarmMap.txt", "w");
		if(_fp != NULL)
		{
			for (int i = 0; i < 100; i++)
			{
				for(int j = 0; j < 100; j++)
				{
					fprintf(_fp, "%d ", _tileMap[_layer][i][j]._tile);
				}
				fprintf(_fp, "\n");
			}
		}
		fclose(_fp);
	}
	if (KEYMANAGER->isOnceKeyDown('L') || KEYMANAGER->isOnceKeyDown('l'))
	{
		fopen_s(&_fp, "FarmMap.txt", "r");
		if (_fp != NULL)
		{
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					fscanf_s(_fp, "%d ", &_tileMap[_layer][i][j]._tile);
					char key[64];
					wsprintf(key, "Tile%d", _tileMap[_layer][i][j]._tile);
					_tileMap[_layer][i][j]._image = IMAGEMANAGER->findImage(key);
				}
				fscanf_s(_fp, "\n");
			}
		}
		fclose(_fp);
	}
}

void MapToolScene::render(void)
{
	// 타일맵 렌더
	PatBlt(_tileMapBuffer->getMemDC(), 0, 0, MapToolWidth, MapToolHeight, WHITENESS);
	for (int i = 0; i < _tileMapSize; i++)
	{
		for (int j = 0; j < _tileMapSize; j++)
		{	
			if (TILEWIDTH * (j + 1) < _cameraPos.x - MapToolWidth / 2 || TILEWIDTH * j > _cameraPos.x + MapToolWidth / 2)
			{
				continue;
			}
			if (TILEWIDTH * (i + 1) < _cameraPos.y - MapToolHeight / 2 || TILEHEIGHT * i > _cameraPos.y + MapToolHeight / 2)
			{
				continue;
			}
			if (_tileMap[_layer][i][j]._image == nullptr)
			{
				DrawRectMake(_tileMapBuffer->getMemDC(), RectMakeCenter(j * TILEWIDTH + TILEWIDTH / 2 - (_cameraPos.x - MapToolWidth / 2), i * TILEHEIGHT + TILEHEIGHT / 2 - (_cameraPos.y - MapToolHeight/ 2), TILEWIDTH, TILEHEIGHT));
			}
			else
			{
				_tileMap[_layer][i][j]._image->render(_tileMapBuffer->getMemDC(), j * TILEWIDTH - (_cameraPos.x - MapToolWidth / 2), i * TILEHEIGHT - (_cameraPos.y - MapToolHeight / 2));
			}
		}
	}
	_tileMapBuffer->render(getMemDC(), 50, 50);
	IMAGEMANAGER->findImage("FarmLayer")->alphaRender(getMemDC(), 50, 50, MapToolWidth, MapToolHeight, _cameraPos.x - MapToolWidth / 2, _cameraPos.y - MapToolHeight / 2, MapToolWidth, MapToolHeight, 128);

	// 선택할 수 있는 타일들
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (_tiles[i][j]._image == nullptr)
			{
				DrawRectMake(_tilesBuffer->getMemDC(), RectMakeCenter(j * TILEWIDTH + TILEWIDTH / 2, i * TILEHEIGHT + TILEHEIGHT / 2, TILEWIDTH, TILEHEIGHT));
			}
			else
			{
				_tiles[i][j]._image->render(_tilesBuffer->getMemDC(),  j * TILEWIDTH , i * TILEHEIGHT);
			}
		}
	}

	_tilesBuffer->render(getMemDC(), 900, 50);

	IMAGEMANAGER->findImage("Cursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
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
