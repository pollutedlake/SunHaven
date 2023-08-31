// 박상현
#include "Stdafx.h"
#include "MapToolScene.h"
#include "../Class/UI.h"


HRESULT MapToolScene::init(void)
{
	_layer = 0;
	_curTiles = 0;
	for(int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			ZeroMemory(&_tileMap, sizeof(_tileMap[i][j]) * 100);
		}
	}
	for(int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			ZeroMemory(&_tiles, sizeof(_tiles[i][j]) * 10);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		_showLayer[i] = false;
	}
	_showLayer[0] = true;
	for(int k = 0; k < 5; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				char _tileName[64];
				wsprintf(_tileName, "Tile%d-%d", k + 1, i * 10 + (j + 1));
				_tiles[k][i][j]._image = IMAGEMANAGER->findImage(_tileName);
				_tiles[k][i][j]._tile = (k + 1) * 1000 + 10 * i + j + 1;
			}
		}
	}
	memset(_tileSizeChar, '\0', sizeof(char) * sizeof(_tileSizeChar) / sizeof(_tileSizeChar[0]));
	_input = true;
	_tileMapBuffer = IMAGEMANAGER->addImage("TileMapBuffer", MapToolWidth, MapToolHeight, true, RGB(255, 255, 255));
	_tilesBuffer = IMAGEMANAGER->addImage("TilesBuffer", TILEWIDTH * 10, TILEHEIGHT  * 10);
	CAMERA->init();
	CAMERA->setPosition({ WINSIZE_X / 2, WINSIZE_Y / 2 });
	_tileMapSize = 100;
	CAMERA->setLimitRight(_tileMapSize * TILEWIDTH - MapToolWidth / 2);
	CAMERA->setLimitBottom(_tileMapSize * TILEHEIGHT - MapToolHeight / 2);
	_cameraPos = { MapToolWidth / 2, MapToolHeight  / 2};

	Button* button = new NormalButton;

	// 
	button->init(1130.0f, 25.0f, 20, 20, "RightButton", bind(&MapToolScene::nextTiles, this));
	_vButton.push_back(button);
	button = new NormalButton;
	button->init(910.0f, 25.0f, 20, 20, "LeftButton", bind(&MapToolScene::prevTiles, this));
	_vButton.push_back(button);

	// 레이어 버튼 추가
	for(int i = 0; i < 5; i++)
	{
		button = new NormalButton;
		char text[64];
		wsprintf(text, "Layer%d", i + 1);
		button->init(1100.0f, 350.0f + 50.f * i, 200, 44, "Button1", bind(&MapToolScene::changeLayer, this, i), text, RGB(255, 255, 255), 30, -15);
		_vButton.push_back(button);
	}
	for (int i = 0; i < 5; i++)
	{
		button = new ToggleButton;
		button->init(950.0f, 350.0f + 50.0f * i, 54, 34, "LayerShowButton", bind(&MapToolScene::toggleShowLayer, this, i), _showLayer[i]);
		_vButton.push_back(button);
	}

	_cursorRC = {NULL, NULL, NULL, NULL};
	_selectRC = { NULL, NULL, NULL, NULL };
	_exPtMouse = {NULL, NULL};
	return S_OK;
}

void MapToolScene::release(void)
{
	for (_viButton = _vButton.begin(); _viButton != _vButton.end();)
	{
		(*_viButton)->release();
		SAFE_DELETE(*_viButton);
		_viButton = _vButton.erase(_viButton);
	}
}

void MapToolScene::update(void)
{
	CAMERA->update();
	for (_viButton = _vButton.begin(); _viButton != _vButton.end(); ++_viButton)
	{
		(*_viButton)->update();
	}

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
	
	RECT rc, rc2;
	rc = RectMake(900, 50, TILEWIDTH * 10, TILEHEIGHT * 10);
	rc2 = RectMake(50, 50, MapToolWidth, MapToolHeight);
	if (PtInRect(&rc, _ptMouse))
	{
		_cursorRC = RectMake(900 + ((_ptMouse.x - 900) / TILEWIDTH) * TILEWIDTH, 50 + ((_ptMouse.y - 50) / TILEHEIGHT) * TILEHEIGHT, TILEWIDTH, TILEHEIGHT);
	}
	else if (PtInRect(&rc2, _ptMouse))
	{
		_cursorRC = RectMake(50 + ((_ptMouse.x - 50) / TILEWIDTH) * TILEWIDTH, 50 + ((_ptMouse.y - 50) / TILEHEIGHT) * TILEHEIGHT, TILEWIDTH, TILEHEIGHT);
	}
	else
	{
		_cursorRC = RectMake( NULL, NULL, NULL, NULL );
	}


	// 마우스 왼쪽 버튼 입력
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&rc, _ptMouse))
		{
			_selectTile = _tiles[_curTiles][(_ptMouse.y - 50) / TILEHEIGHT][(_ptMouse.x - 900) / TILEWIDTH];
			_selectRC = _cursorRC;
		}
		for (_viButton = _vButton.begin(); _viButton != _vButton.end(); ++_viButton)
		{
			(*_viButton)->buttonDown();
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&rc2, _ptMouse))
		{
			_tileMap[_layer][(_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) / TILEHEIGHT][(_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) / TILEWIDTH] = _selectTile;
			cout << (_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) / TILEWIDTH << "\t" << (_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) / TILEHEIGHT << endl;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (_viButton = _vButton.begin(); _viButton != _vButton.end(); ++_viButton)
		{
			(*_viButton)->buttonUp(NULL);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (PtInRect(&rc, _ptMouse))
		{
			_exPtMouse = _ptMouse;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (PtInRect(&rc, _ptMouse))
		{
			_selectRC = RectMake(min((_ptMouse.x - 900) / TILEWIDTH, (_exPtMouse.x - 900) / TILEWIDTH) * TILEWIDTH + 900,
				min((_ptMouse.y - 50) / TILEHEIGHT, (_exPtMouse.y - 50) / TILEHEIGHT) * TILEHEIGHT + 50,
				(abs((_ptMouse.x - 900) / TILEWIDTH - (_exPtMouse.x - 900) / TILEWIDTH) + 1) * TILEWIDTH,
				(abs((_ptMouse.y - 50) / TILEHEIGHT - (_exPtMouse.y - 50) / TILEHEIGHT) + 1) * TILEHEIGHT);
		}
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_selectRC = _cursorRC;
	}*/
	
	// 세이브
	if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('s'))
	{
		saveMaps();
	}

	// 로드
	if (KEYMANAGER->isOnceKeyDown('L') || KEYMANAGER->isOnceKeyDown('l'))
	{
		loadLayers();
	}
}

void MapToolScene::render(void)
{
	// 타일맵 렌더
	PatBlt(_tileMapBuffer->getMemDC(), 0, 0, MapToolWidth, MapToolHeight, WHITENESS);
	for (int i = 0; i <= 100; i++)
	{
		LineMake(_tileMapBuffer->getMemDC(), - (_cameraPos.x - MapToolWidth / 2), TILEHEIGHT * i - (_cameraPos.y - MapToolHeight / 2), 
			TILEWIDTH * 100 - (_cameraPos.x - MapToolWidth / 2), TILEHEIGHT * i - (_cameraPos.y - MapToolHeight / 2));
		LineMake(_tileMapBuffer->getMemDC(), TILEWIDTH * i - (_cameraPos.x - MapToolWidth / 2), - (_cameraPos.y - MapToolHeight / 2),
		TILEWIDTH * i - (_cameraPos.x - MapToolWidth / 2), TILEHEIGHT * 100 - (_cameraPos.y - MapToolHeight / 2));
	}
	ZeroMemory(&_tileMap[5], sizeof(_tileMap[0]));
	for(int k= 0; k <5; k++)
	{
		if (!_showLayer[k])
		{
			continue;
		}
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
				if (_tileMap[k][i][j]._image != nullptr)
				{
					_tileMap[k][i][j]._image->render(_tileMapBuffer->getMemDC(), j * TILEWIDTH - (_cameraPos.x - MapToolWidth / 2), i * TILEHEIGHT - (_cameraPos.y - MapToolHeight / 2));
				}
			}
		}
	}
	_tileMapBuffer->render(getMemDC(), 50, 50);
	char text[64];
	wsprintf(text, "FarmLayer%d", _layer + 1);
	switch (_layer)
	{
		case 1:
			IMAGEMANAGER->findImage(text)->alphaRender(getMemDC(), 50 - (_cameraPos.x - MapToolWidth / 2), 50 - (_cameraPos.y - MapToolHeight / 2), 128);
		break;
		case 2:
			IMAGEMANAGER->findImage(text)->alphaRender(getMemDC(), 50 - (_cameraPos.x - MapToolWidth / 2), 50 - (_cameraPos.y - MapToolHeight / 2), 128);
			break;
		case 3:
			IMAGEMANAGER->findImage(text)->alphaRender(getMemDC(), 50 - (_cameraPos.x - MapToolWidth / 2), 50 - (_cameraPos.y - MapToolHeight / 2), 128);
			break;
		case 4:
			IMAGEMANAGER->findImage(text)->alphaRender(getMemDC(), 50 - (_cameraPos.x - MapToolWidth / 2), 50 - (_cameraPos.y - MapToolHeight / 2), 128);
			break;
	}

	// 선택할 수 있는 타일들
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (_tiles[_curTiles][i][j]._image == nullptr)
			{
				DrawRectMake(_tilesBuffer->getMemDC(), RectMakeCenter(j * TILEWIDTH + TILEWIDTH / 2, i * TILEHEIGHT + TILEHEIGHT / 2, TILEWIDTH, TILEHEIGHT));
			}
			else
			{
				_tiles[_curTiles][i][j]._image->render(_tilesBuffer->getMemDC(),  j * TILEWIDTH , i * TILEHEIGHT);
			}
		}
	}
	_tilesBuffer->render(getMemDC(), 900, 50);

	// 버튼 렌더
	for (_viButton = _vButton.begin(); _viButton != _vButton.end(); ++_viButton)
	{
		(*_viButton)->render();
	}

	HPEN cursorPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN selectPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), cursorPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), (HBRUSH)GetStockObject(NULL_BRUSH));
	DrawRectMake(getMemDC(), _cursorRC);
	SelectObject(getMemDC(), selectPen);
	DrawRectMake(getMemDC(), _selectRC);
	SelectObject(getMemDC(), oldBrush);
	SelectObject(getMemDC(), oldPen);
	DeleteObject(cursorPen);
	DeleteObject(selectPen);

	// 마우스 커서
	IMAGEMANAGER->findImage("Cursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

void MapToolScene::changeLayer(int layerN)
{
	_layer = layerN;
}

void MapToolScene::toggleShowLayer(int layer)
{
	_showLayer[layer] = !_showLayer[layer];
}

void MapToolScene::saveMaps()
{
	FILE* _fp;
	fopen_s(&_fp, "FarmMap.txt", "w");
	if (_fp != NULL)
	{
		for(int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				for (int k = 0; k < 100; k++)
				{
					fprintf(_fp, "%d ", _tileMap[i][j][k]._tile);
				}
				fprintf(_fp, "\n");
			}
			fprintf(_fp, "\n");
		}
	}
	std::fclose(_fp);
}

void MapToolScene::loadLayers()
{
	FILE* _fp;
	fopen_s(&_fp, "FarmMap.txt", "r");
	if (_fp != NULL)
	{
		for(int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				for (int k = 0; k < 100; k++)
				{
					fscanf_s(_fp, "%d ", &_tileMap[i][j][k]._tile);
					//_tileMap[i][j][k]._tile += 1000;
					char key[64];
					wsprintf(key, "Tile%d-%d", _tileMap[i][j][k]._tile / 1000, _tileMap[i][j][k]._tile % 1000);
					_tileMap[i][j][k]._image = IMAGEMANAGER->findImage(key);
				}
				fscanf_s(_fp, "\n");
			}
			fscanf_s(_fp, "\n");
		}
	}
	std::fclose(_fp);
}
