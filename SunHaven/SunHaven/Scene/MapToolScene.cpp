// 박상현
#include "Stdafx.h"
#include "MapToolScene.h"
#include "../Class/UI/Buttons.h"
#include "../Class/Object/Grass.h"
#include "../Class/Object/Tree.h"
#include "../Class/Object/Rock.h"


HRESULT MapToolScene::init(void)
{
	_layer = 0;
	_curTiles = 0;
	_tileMapSize = 100;
	for(int i = 0; i < 7; i++)
	{
		for (int j = 0; j < _tileMapSize; j++)
		{
			ZeroMemory(&_tileMap, sizeof(_tileMap[i][j]) * _tileMapSize);
		}
	}
	for(int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			ZeroMemory(&_tiles, sizeof(_tiles[i][j]) * 10);
		}
	}
	for (int i = 0; i < 7; i++)
	{
		_showLayer[i] = false;
	}
	_showLayer[0] = true;
	for(int k = 0; k < 10; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				char _tileName[64];
				wsprintf(_tileName, "Tile%d-%d", k + 1, i * 10 + (j + 1));
				_tiles[k][i][j]._image = IMAGEMANAGER->findImage(_tileName);
				_tiles[k][i][j]._tile = (k + 1) * 1000 + 10 * i + j + 1;
				_tiles[k][i][j]._object = nullptr;
			}
		}
	}
	memset(_tileSizeChar, '\0', sizeof(char) * sizeof(_tileSizeChar) / sizeof(_tileSizeChar[0]));
	_input = true;
	_tileMapBuffer = IMAGEMANAGER->addImage("TileMapBuffer", TILEWIDTH * _tileMapSize, TILEWIDTH * _tileMapSize, true, RGB(255, 255, 255));
	_tilesBuffer = IMAGEMANAGER->addImage("TilesBuffer", TILEWIDTH * 10, TILEHEIGHT  * 10);
	_collisionBuffer = IMAGEMANAGER->addImage("CollisionBuffer", TILEWIDTH * _tileMapSize, TILEWIDTH * _tileMapSize, true,  RGB(0, 0, 0));
	_cameraPos = { MapToolWidth / 2, MapToolHeight  / 2};

	NormalButton* normalButton = new NormalButton;

	// 
	normalButton->init(1130.0f, 25.0f, 20, 20, "RightButton", bind(&MapToolScene::nextTiles, this));
	_vNormalButton.push_back(normalButton);
	normalButton = new NormalButton;
	normalButton->init(910.0f, 25.0f, 20, 20, "LeftButton", bind(&MapToolScene::prevTiles, this));
	_vNormalButton.push_back(normalButton);

	// Save, Load 버튼
	normalButton = new NormalButton;
	normalButton->init(950.0f, 700.0f, 100, 44, "Button1", bind(&MapToolScene::saveMaps, this), "Save", RGB(255, 255, 255), 30, -15);
	_vNormalButton.push_back(normalButton);
	normalButton = new NormalButton;
	normalButton->init(1050.0f, 700.0f, 100, 44, "Button1", bind(&MapToolScene::loadLayers, this), "Load", RGB(255, 255, 255), 30, -15);
	_vNormalButton.push_back(normalButton);
	normalButton = new NormalButton;
	normalButton->init(1150.0f, 700.0f, 100, 44, "Button1", bind(&MapToolScene::erase, this), "Erase", RGB(255, 255, 255), 30, -15);
	_vNormalButton.push_back(normalButton);

	// Object 버튼
	char* objectStr[] = { "풀1", "풀2", "나무1", "나무2", "돌1", "돌2" };
	for (int i = 0; i < 6; i++)
	{
		normalButton = new NormalButton;
		normalButton->init(75.0f + 50 * i, 50.0f + MapToolHeight + 25, 50, 50, "Button1", bind(&MapToolScene::selectObject, this, i), objectStr[i], 
			RGB(255, 255, 255), 25, -15);
		_vNormalButton.push_back(normalButton);
	}

	// Layer 선택 버튼
	RadioButton* radioButton = new RadioButton;
	float x[] = { 1100.0f, 1100.0f, 1100.0f, 1100.0f, 1100.0f, 1100.0f, 1100.0f };
	float y[] = { 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f };
	int width[] = { 200, 200, 200, 200, 200, 200, 200 };
	int height[] = { 44, 44, 44, 44, 44, 44, 44 };
	char* str[] = { "Layer1", "Layer2", "Layer3", "Layer4", "Layer5", "Collider", "Object" };
	function<void(int)> f[7];
	for (int i = 0; i < 7; i++)
	{
			f[i] = bind(&MapToolScene::changeLayer, this, i);
	}
	radioButton->init(7, x, y, width, height, "Button1", f, str, RGB(255, 255, 255), 30, -15);
	_vRadioButton.push_back(radioButton);

	// Layer보이는 버튼
	ToggleButton* toggleButton;
	for (int i = 0; i < 7; i++)
	{
		toggleButton = new ToggleButton;
		toggleButton->init(950.0f, 350.0f + 50.0f * i, 54, 34, "LayerShowButton", bind(&MapToolScene::toggleShowLayer, this, i), _showLayer[i]);
		_vToggleButton.push_back(toggleButton);
	}

	_cursorRC = {NULL, NULL, NULL, NULL};
	_selectRC = { NULL, NULL, NULL, NULL };
	_tilesRC = RectMake(900, 50, TILEWIDTH * 10, TILEHEIGHT * 10);
	_mapToolRC = RectMake(50, 50, MapToolWidth, MapToolHeight);
	_selectTilesRow = 1;
	_selectTilesCol = 1;
	return S_OK;
}

void MapToolScene::release(void)
{
	for (_viNormalButton = _vNormalButton.begin(); _viNormalButton != _vNormalButton.end();)
	{
		(*_viNormalButton)->release();
		SAFE_DELETE(*_viNormalButton);
		_viNormalButton = _vNormalButton.erase(_viNormalButton);
	}
	for (_viRadioButton = _vRadioButton.begin(); _viRadioButton != _vRadioButton.end();)
	{
		(*_viRadioButton)->release();
		SAFE_DELETE(*_viRadioButton);
		_viRadioButton = _vRadioButton.erase(_viRadioButton);
	}
	for (_viToggleButton = _vToggleButton.begin(); _viToggleButton != _vToggleButton.end();)
	{
		(*_viToggleButton)->release();
		SAFE_DELETE(*_viToggleButton);
		_viToggleButton = _vToggleButton.erase(_viToggleButton);
	}
}

void MapToolScene::update(void)
{
	for (_viNormalButton = _vNormalButton.begin(); _viNormalButton != _vNormalButton.end(); ++_viNormalButton)
	{
		(*_viNormalButton)->update();
	}
	for (_viToggleButton = _vToggleButton.begin(); _viToggleButton != _vToggleButton.end(); ++_viToggleButton)
	{
		(*_viToggleButton)->update();
	}
	for (_viRadioButton = _vRadioButton.begin(); _viRadioButton != _vRadioButton.end(); ++_viRadioButton)
	{
		(*_viRadioButton)->update();
	}
	

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_cameraPos.y -= 10;
		if (_cameraPos.y < MapToolHeight / 2)
		{
			_cameraPos.y = MapToolHeight / 2;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cameraPos.y += 10;
		if( _cameraPos.y > TILEHEIGHT * _tileMapSize - MapToolHeight / 2)
		{
			_cameraPos.y = TILEHEIGHT * _tileMapSize - MapToolHeight / 2;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cameraPos.x -= 10;
		if (_cameraPos.x < MapToolWidth / 2)
		{
			_cameraPos.x = MapToolWidth / 2;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cameraPos.x += 10;
		if (_cameraPos.x > TILEWIDTH * _tileMapSize - MapToolWidth / 2)
		{
			_cameraPos.x = TILEWIDTH * _tileMapSize - MapToolWidth / 2;
		}
	}
	
	if (PtInRect(&_tilesRC, _ptMouse))
	{
		_cursorRC = RectMake(900 + ((_ptMouse.x - 900) / TILEWIDTH) * TILEWIDTH, 50 + ((_ptMouse.y - 50) / TILEHEIGHT) * TILEHEIGHT, TILEWIDTH, TILEHEIGHT);
	}
	else if (PtInRect(&_mapToolRC, _ptMouse))
	{
		_cursorRC = RectMake(_ptMouse.x - (_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) % TILEWIDTH, _ptMouse.y - (_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) % TILEHEIGHT, 
			TILEWIDTH * _selectTilesCol, TILEHEIGHT * _selectTilesRow);
	}
	else
	{
		_cursorRC = RectMake( NULL, NULL, NULL, NULL );
	}


	// 마우스 왼쪽 버튼 입력
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (_viNormalButton = _vNormalButton.begin(); _viNormalButton != _vNormalButton.end(); ++_viNormalButton)
		{
			(*_viNormalButton)->buttonDown();
		}
		for (_viToggleButton = _vToggleButton.begin(); _viToggleButton != _vToggleButton.end(); ++_viToggleButton)
		{
			(*_viToggleButton)->buttonDown();
		}
		for (_viRadioButton = _vRadioButton.begin(); _viRadioButton != _vRadioButton.end(); ++_viRadioButton)
		{
			(*_viRadioButton)->buttonDown();
		}
		if (PtInRect(&_tilesRC, _ptMouse))
		{
			if (PtInRect(&_mapToolRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
			{
				for (int i = 0; i < (_selectRC.bottom - _selectRC.top) / TILEHEIGHT; i++)
				{
					for (int j = 0; j < (_selectRC.right - _selectRC.left) / TILEWIDTH; j++)
					{
						_tileMap[_layer][_selectRC.top / TILEHEIGHT + i][_selectRC.left / TILEWIDTH + j] = _tiles[_curTiles][(_cursorRC.top - 50) / TILEHEIGHT][(_cursorRC.left - 900) / TILEWIDTH];
					}
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_mapToolRC, _ptMouse))
		{	
			for (int i = 0; i < _selectTilesRow; i++)
			{
				CopyMemory(&_tileMap[_layer][(_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) / TILEHEIGHT + i][(_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) / TILEWIDTH],
					&_selectTiles[i][0], sizeof(Tile) * _selectTilesCol);
				for (int j = 0; j < _selectTilesCol; j++)
				{
					if (_selectTiles[i][j]._object == nullptr)
					{
						continue;
					}
					Object* object = new Object(*_selectTiles[i][j]._object);
					object->setTilePos(PointMake((_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) / TILEWIDTH + j, (_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) / TILEHEIGHT + i));
					_tileMap[6][(_ptMouse.y - 50 + _cameraPos.y - MapToolHeight / 2) / TILEHEIGHT + i][(_ptMouse.x - 50 + _cameraPos.x - MapToolWidth / 2) / TILEWIDTH + j]._object = object;
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (_viNormalButton = _vNormalButton.begin(); _viNormalButton != _vNormalButton.end(); ++_viNormalButton)
		{
			(*_viNormalButton)->buttonUp(NULL);
		}
		for (_viToggleButton = _vToggleButton.begin(); _viToggleButton != _vToggleButton.end(); ++_viToggleButton)
		{
			(*_viToggleButton)->buttonUp(NULL);
		}
		for (_viRadioButton = _vRadioButton.begin(); _viRadioButton != _vRadioButton.end(); ++_viRadioButton)
		{
			(*_viRadioButton)->buttonUp(NULL);
		}
	}

	static RECT rc2 = {NULL, NULL, NULL, NULL};
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (PtInRect(&_tilesRC, _ptMouse))
		{
			_exCursorRC = _cursorRC;
		}
		else if (PtInRect(&_mapToolRC, _ptMouse))
		{
			_exCursorRC = _cursorRC;
			rc2 = RectMake(_exCursorRC.left - 50 + _cameraPos.x - MapToolWidth / 2, _exCursorRC.top - 50 + _cameraPos.y - MapToolHeight / 2, TILEWIDTH, TILEHEIGHT);
		}
		else
		{
			_exCursorRC = {NULL, NULL, NULL, NULL};
		}
		_selectTilesCol = 1;
		_selectTilesRow = 1;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		RECT rc;
		if (PtInRect(&_tilesRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
		{
			if(PtInRect(&_tilesRC, _ptMouse))
			{
				rc = RectMake(_cursorRC.left, _cursorRC.top, TILEWIDTH, TILEHEIGHT);
				_selectRC = RectMake(min(_exCursorRC.left, rc.left), min(_exCursorRC.top, rc.top), abs(_exCursorRC.left - rc.left) + TILEWIDTH, abs(_exCursorRC.top - rc.top) + TILEHEIGHT);
			}
			if (_ptMouse.x < _tilesRC.left)
			{
				_selectRC.left = _tilesRC.left;
			}
			if (_ptMouse.x > _tilesRC.right)
			{
				_selectRC.right = _tilesRC.right;
			}
			if (_ptMouse.y < _tilesRC.top)
			{
				_selectRC.top = _tilesRC.top;
			}
			if (_ptMouse.y > _tilesRC.bottom)
			{
				_selectRC.bottom = _tilesRC.bottom;
			}
		}
		else if (PtInRect(&_mapToolRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
		{
			if(PtInRect(&_mapToolRC, _ptMouse))
			{
				rc = RectMake(_cursorRC.left - 50 + _cameraPos.x - MapToolWidth / 2, _cursorRC.top - 50 + _cameraPos.y - MapToolHeight / 2, TILEWIDTH, TILEHEIGHT);
				_selectRC = RectMake(min(rc2.left, rc.left), min(rc2.top, rc.top), abs(rc2.left - rc.left) + TILEWIDTH, abs(rc2.top - rc.top) + TILEHEIGHT);
			}
			if (_ptMouse.x < _mapToolRC.left)
			{
				_selectRC.left = (_cameraPos.x - MapToolWidth / 2) / TILEWIDTH * TILEWIDTH;
				if (_selectRC.left < 0)
				{
					_selectRC.left = 0;
				}
			}
			if (_ptMouse.x > _mapToolRC.right)
			{
				_selectRC.right = ((_cameraPos.x + MapToolWidth / 2) / TILEWIDTH + 1) * TILEWIDTH;
				if (_selectRC.right > TILEWIDTH * 100)
				{
					_selectRC.right = TILEWIDTH * 100;
				}
			}
			if (_ptMouse.y < _mapToolRC.top)
			{
				_selectRC.top = (_cameraPos.y - MapToolHeight / 2) / TILEHEIGHT * TILEHEIGHT;
				if (_selectRC.top < 0)
				{
					_selectRC.top = 0;
				}
			}
			if (_ptMouse.y > _mapToolRC.bottom)
			{
				_selectRC.bottom = ((_cameraPos.y + MapToolHeight / 2) / TILEHEIGHT + 1) * TILEHEIGHT;
				if (_selectRC.bottom > TILEWIDTH * 100)
				{
					_selectRC.bottom = TILEWIDTH * 100;
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		copyTiles();
	}
}

void MapToolScene::render(void)
{
	// 타일맵 렌더
	PatBlt(_tileMapBuffer->getMemDC(), 0, 0, TILEWIDTH * _tileMapSize, TILEWIDTH * _tileMapSize, WHITENESS);
	for (int i = 0; i <= _tileMapSize; i++)
	{
		LineMake(_tileMapBuffer->getMemDC(), 0, TILEHEIGHT * i,	TILEWIDTH * _tileMapSize, TILEHEIGHT * i);
		LineMake(_tileMapBuffer->getMemDC(), TILEWIDTH * i, 0, TILEWIDTH * i, TILEHEIGHT * _tileMapSize);
	}
	//ZeroMemory(&_tileMap[5], sizeof(_tileMap[0]));
	for(int k = 0; k < 5; k++)
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
					_tileMap[k][i][j]._image->render(_tileMapBuffer->getMemDC(), j * TILEWIDTH, i * TILEHEIGHT);
				}
				/*else if (_tileMap[6][i][j]._object != nullptr)
				{
					_tileMap[6][i][j]._object->render(_tileMapBuffer->getMemDC());
				}*/
			}
		}
	}
	if (_showLayer[6])
	{
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
				if (_tileMap[6][i][j]._object != nullptr)
				{
					_tileMap[6][i][j]._object->render(_tileMapBuffer->getMemDC());
				}
			}
		}
	}
	/*
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
	}*/

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
	HPEN selectPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	if (PtInRect(&_tilesRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
	{
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), selectPen);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), (HBRUSH)GetStockObject(NULL_BRUSH));
		DrawRectMake(getMemDC(), _selectRC);
		SelectObject(getMemDC(), oldBrush);
		SelectObject(getMemDC(), oldPen);
	}
	else if(PtInRect(&_mapToolRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
	{
		HPEN oldPen = (HPEN)SelectObject(_tileMapBuffer->getMemDC(), selectPen);
		HBRUSH oldBrush = (HBRUSH)SelectObject(_tileMapBuffer->getMemDC(), (HBRUSH)GetStockObject(NULL_BRUSH));
		DrawRectMake(_tileMapBuffer->getMemDC(), RectMake(_selectRC.left, _selectRC.top, _selectRC.right - _selectRC.left, _selectRC.bottom - _selectRC.top));
		SelectObject(_tileMapBuffer->getMemDC(), oldBrush);
		SelectObject(_tileMapBuffer->getMemDC(), oldPen);
	}
	DeleteObject(selectPen);
	_tileMapBuffer->render(getMemDC(), 50, 50, MapToolWidth, MapToolHeight, _cameraPos.x - MapToolWidth / 2, _cameraPos.y - MapToolHeight / 2, MapToolWidth, MapToolHeight);
	PatBlt(_collisionBuffer->getMemDC(), 0, 0, TILEWIDTH * 100, TILEHEIGHT * 100, WHITENESS);
	if (_showLayer[5])
	{
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
				if (_tileMap[5][i][j]._image != nullptr)
				{
					_tileMap[5][i][j]._image->render(_collisionBuffer->getMemDC(), j * TILEWIDTH, i * TILEHEIGHT);
				}
			}
		}
		_collisionBuffer->alphaRender(getMemDC(), 50, 50, MapToolWidth, MapToolHeight, _cameraPos.x - MapToolWidth / 2, _cameraPos.y - MapToolHeight / 2, MapToolWidth, MapToolHeight, 128);
	}

	// 버튼 렌더
	for (_viNormalButton = _vNormalButton.begin(); _viNormalButton != _vNormalButton.end(); ++_viNormalButton)
	{
		(*_viNormalButton)->render();
	}
	for (_viToggleButton = _vToggleButton.begin(); _viToggleButton != _vToggleButton.end(); ++_viToggleButton)
	{
		(*_viToggleButton)->render();
	}
	for (_viRadioButton = _vRadioButton.begin(); _viRadioButton != _vRadioButton.end(); ++_viRadioButton)
	{
		(*_viRadioButton)->render();
	}

	if(PtInRect(&_mapToolRC, _ptMouse))
	{
		for (int i = 0; i < _selectTilesRow; i++)
		{
			for (int j = 0; j < _selectTilesCol; j++)
			{
				if (_selectTiles[i][j]._image == nullptr)
				{
					if (_selectTiles[i][j]._object != nullptr)
					{
						_selectTiles[i][j]._object->renderToPoint(PointMake(_ptMouse.x + TILEWIDTH * j, _ptMouse.y + TILEHEIGHT * i));
					}
					continue;;
				}
				_selectTiles[i][j]._image->alphaRender(getMemDC(), _cursorRC.left + TILEWIDTH * j, _cursorRC.top + TILEHEIGHT * i, 128);
			}
		}
	}

	HPEN cursorPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), cursorPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), (HBRUSH)GetStockObject(NULL_BRUSH));
	DrawRectMake(getMemDC(), _cursorRC);
	SelectObject(getMemDC(), oldBrush);
	SelectObject(getMemDC(), oldPen);
	DeleteObject(cursorPen);

	// 마우스 커서
	IMAGEMANAGER->findImage("Cursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Title");
	}
}

void MapToolScene::changeLayer(int layerN)
{
	_layer = layerN;
}

void MapToolScene::prevTiles(void)
{
	_curTiles--; if (_curTiles < 0) _curTiles = 9; PatBlt(_tilesBuffer->getMemDC(), 0, 0, TILEWIDTH * 10, TILEHEIGHT * 10, WHITENESS);
}


void MapToolScene::nextTiles(void)
{
	_curTiles++; if (_curTiles > 9) _curTiles = 0; PatBlt(_tilesBuffer->getMemDC(), 0, 0, TILEWIDTH * 10, TILEHEIGHT * 10, WHITENESS);
}

void MapToolScene::erase(void)
{
	if (PtInRect(&_mapToolRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
	{
		for (int i = 0; i < _selectTilesRow; i++)
		{
			ZeroMemory(&_tileMap[_layer][_selectRC.top / TILEHEIGHT + i][_selectRC.left / TILEWIDTH], sizeof(Tile) * _selectTilesCol);
		}
	}
}

void MapToolScene::toggleShowLayer(int layer)
{
	_showLayer[layer] = !_showLayer[layer];
}

void MapToolScene::selectObject(int objectType)
{
	char str[64];
	wsprintf(str, "Object%d", objectType + 1);
	_selectTiles[0][0]._image = IMAGEMANAGER->findImage(str);
	Object* object = nullptr;
	switch (objectType / 2)
	{
		case 0:
			object = new Grass;
		break;
		case 1:
			object = new Tree;
		break;
		case 2:
			object = new Rock;
		break;
	}
	if (object == nullptr)
	{
		return;
	}
	object->init((LivingObjectType)objectType);
	for (int i = 0; i < MapToolWidth / TILEWIDTH + 1; i++)
	{
		ZeroMemory(&_selectTiles[i], sizeof(Tile) * MapToolHeight / TILEHEIGHT + 1);
	}
	_selectTiles[0][0]._object = object;
	_selectTilesRow = 1;
	_selectTilesCol = 1;
	_selectRC = { NULL, NULL, NULL, NULL };
	changeLayer(6);
}

void MapToolScene::copyTiles(void)
{
	for (int i = 0; i < MapToolWidth / TILEWIDTH + 1; i++)
	{
		ZeroMemory(&_selectTiles[i], sizeof(Tile) * MapToolHeight / TILEHEIGHT + 1);
	}
	_selectTilesRow = (_selectRC.bottom - _selectRC.top) / TILEHEIGHT;
	_selectTilesCol = (_selectRC.right - _selectRC.left) / TILEWIDTH;
	if(PtInRect(&_tilesRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
	{
		for (int i = 0; i < _selectTilesRow; i++)
		{
			CopyMemory(&_selectTiles[i][0], &_tiles[_curTiles][(_selectRC.top - 50) / TILEHEIGHT + i][(_selectRC.left - 900) / TILEWIDTH], 
				sizeof(Tile) * _selectTilesCol);
		}
	}
	else if (PtInRect(&_mapToolRC, PointMake(_exCursorRC.left, _exCursorRC.top)))
	{
		for (int i = 0; i < _selectTilesRow; i++)
		{
			CopyMemory(&_selectTiles[i][0], 
				&_tileMap[_layer][_selectRC.top / TILEHEIGHT + i][_selectRC.left / TILEWIDTH], sizeof(Tile) * _selectTilesCol);
		}
	}
}

void MapToolScene::saveMaps()
{
	FILE* _fp;
	fopen_s(&_fp, "FarmMap.txt", "w");
	if (_fp != NULL)
	{
		for(int i = 0; i < 6; i++)
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

	fopen_s(&_fp, "FarmMapObject.txt", "w");
	if (_fp != NULL)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int k = 0; k < 100; k++)
			{
				if (_tileMap[6][j][k]._object == nullptr)
				{
					fprintf(_fp, "%d ", -1);
				}
				else
				{
					fprintf(_fp, "%d ", (int)(_tileMap[6][j][k]._object->getType()));
				}
			}
			fprintf(_fp, "\n");
		}
		fprintf(_fp, "\n");
	}
	std::fclose(_fp);

	PatBlt(_tileMapBuffer->getMemDC(), 0, 0, TILEWIDTH * _tileMapSize, TILEWIDTH * _tileMapSize, WHITENESS);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < _tileMapSize; j++)
		{
			for (int k = 0; k < _tileMapSize; k++)
			{
				if (_tileMap[i][j][k]._image == nullptr)
				{
					continue;
				}
				_tileMap[i][j][k]._image->render(_tileMapBuffer->getMemDC(), TILEWIDTH * k, TILEHEIGHT * j);
			}
		}
	}

	BITMAP bitmap;
	GetObject(_tileMapBuffer->getImageInfo()->hBit, sizeof(BITMAP), &bitmap);
	BITMAPINFOHEADER bi;
	ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;

	GetDIBits(_tileMapBuffer->getMemDC(), _tileMapBuffer->getImageInfo()->hBit, 0, bitmap.bmHeight, NULL, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);
	LPBYTE lpBits = new BYTE[bi.biSizeImage];
	GetDIBits(_tileMapBuffer->getMemDC(), _tileMapBuffer->getImageInfo()->hBit, 0, bitmap.bmHeight, lpBits, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	HANDLE hFile = CreateFile("FarmMap.bmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		delete[] lpBits;
		return;
	}

	BITMAPFILEHEADER bmfHeader;
	bmfHeader.bfType = 'MB';
	bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfHeader.bfSize = bmfHeader.bfOffBits + bi.biSizeImage;
	bmfHeader.bfReserved1 = bmfHeader.bfReserved2 = 0;

	DWORD dwWritten;
	WriteFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(hFile, &bi, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hFile, lpBits, bi.biSizeImage, &dwWritten, NULL);
	CloseHandle(hFile);

	PatBlt(_tileMapBuffer->getMemDC(), 0, 0, TILEWIDTH * _tileMapSize, TILEWIDTH * _tileMapSize, WHITENESS);
	ZeroMemory(lpBits, sizeof(BYTE) * bi.biSizeImage);
	for (int j = 0; j < _tileMapSize; j++)
	{
		for (int k = 0; k < _tileMapSize; k++)
		{
			if (_tileMap[5][j][k]._image == nullptr)
			{
				continue;
			}
			_tileMap[5][j][k]._image->render(_tileMapBuffer->getMemDC(), TILEWIDTH * k, TILEHEIGHT * j);
		}
	}
	GetDIBits(_tileMapBuffer->getMemDC(), _tileMapBuffer->getImageInfo()->hBit, 0, bitmap.bmHeight, NULL, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);
	GetDIBits(_tileMapBuffer->getMemDC(), _tileMapBuffer->getImageInfo()->hBit, 0, bitmap.bmHeight, lpBits, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);
	hFile = CreateFile("FarmMapCollision.bmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		delete[] lpBits;
		return;
	}

	WriteFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(hFile, &bi, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hFile, lpBits, bi.biSizeImage, &dwWritten, NULL);
	CloseHandle(hFile);
	delete[] lpBits;
}

void MapToolScene::loadLayers()
{
	FILE* _fp;
	fopen_s(&_fp, "FarmMap.txt", "r");
	if (_fp != NULL)
	{
		for(int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				for (int k = 0; k < 100; k++)
				{
					int tile;
					fscanf_s(_fp, "%d ", &tile);
					tile--;
					_tileMap[i][j][k] = _tiles[tile / 1000 - 1][(tile % 100) / 10][tile % 10];
				}
				fscanf_s(_fp, "\n");
			}
			fscanf_s(_fp, "\n");
		}
	}
	std::fclose(_fp);

	fopen_s(&_fp, "FarmMapObject.txt", "r");
	if (_fp != NULL)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int k = 0; k < 100; k++)
			{
				int tile;
				fscanf_s(_fp, "%d ", &tile);
				if (tile == -1)
				{
					continue;
				}
				//Object* object = new Object;
				Object* object = nullptr;
				switch (tile / 2)
				{
				case 0:
					object = new Grass;
					break;
				case 1:
					object = new Tree;
					break;
				case 2:
					object = new Rock;
					break;
				}
				if (object == nullptr)
				{
					return;
				}
				object->init((LivingObjectType)tile, PointMake(k, j));
				_tileMap[6][j][k]._object = object;
			}
			fscanf_s(_fp, "\n");
		}
		fscanf_s(_fp, "\n");
	}
	std::fclose(_fp);
}
