// ¹Ú»óÇö
#pragma once
#include "../FrameWork/GameNode/GameNode.h"

#define MapToolWidth	800
#define MapToolHeight	600


struct Tile
{
	GImage* _image = nullptr;
	int _tile = 0;
};

class Button;

class MapToolScene : public GameNode
{
private:
	GImage* _tileMapBuffer;
	Tile _tileMap[6][100][100];
	int _tileMapSize;

	GImage* _tilesBuffer;
	Tile _tiles[5][20][20];

	vector<Button*> _vButton;
	vector<Button*>::iterator _viButton;

	Tile _selectTile;
	POINT _cameraPos;
	char _tileSizeChar[20];
	bool _input;
	int _layer;
	int _curTiles;

	bool _showLayer[5];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void changeLayer(int layer);

	void prevTiles(void) { _curTiles--; if (_curTiles < 0) _curTiles = 4; }
	void nextTiles(void) { _curTiles++; if (_curTiles > 4) _curTiles = 0; }

	void toggleShowLayer(int layer);

	void saveMaps();
	void loadLayers();

	MapToolScene() {}
	~MapToolScene() {}
};
