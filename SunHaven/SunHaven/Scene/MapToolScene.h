// ¹Ú»óÇö
#pragma once
#include "../FrameWork/GameNode/GameNode.h"

#define MapToolWidth	800
#define MapToolHeight	600

class Object;

enum TileType
{
	NORMAL,
	COLLIDER,
	OBJECT
};

enum Map
{
	FARM,
	MINE,
	DYNUS
};

struct Tile
{
	GImage* _image = nullptr;
	int _tile = 0;
	Object* _object = nullptr;
};

class NormalButton;
class ToggleButton;
class RadioButton;

class MapToolScene : public GameNode
{
private:
	GImage* _tileMapBuffer;
	Tile _tileMap[4][7][100][100];
	int _tileMapSize;

	GImage* _tilesBuffer;
	Tile _tiles[10][20][20];

	GImage* _collisionBuffer;

	vector<NormalButton*> _vNormalButton;
	vector<NormalButton*>::iterator _viNormalButton;
	vector<ToggleButton*> _vToggleButton;
	vector<ToggleButton*>::iterator _viToggleButton;
	vector<RadioButton*> _vRadioButton;
	vector<RadioButton*>::iterator _viRadioButton;

	Tile _selectTiles[MapToolWidth / TILEWIDTH + 1][MapToolHeight / TILEHEIGHT + 1];

	POINT _cameraPos;
	char _tileSizeChar[20];
	bool _input;
	int _layer;
	int _curMap;
	int _curTiles;

	RECT _cursorRC;
	RECT _selectRC;
	RECT _tilesRC;
	RECT _mapToolRC;
	RECT _exCursorRC;

	int _selectTilesRow;
	int _selectTilesCol;

	bool _showLayer[7];
	char* _mapName[4];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void changeLayer(int layer);
	void changeMap(int map);

	void prevTiles(void);
	void nextTiles(void);
	void erase(void);
	void toggleShowLayer(int layer);
	void selectObject(int objectType);

	void copyTiles(void);
	void Exit(void);

	void saveMaps();
	void loadLayers();

	MapToolScene() {}
	~MapToolScene() {}
};
