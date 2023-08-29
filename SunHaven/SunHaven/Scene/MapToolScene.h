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

class MapToolScene : public GameNode
{
private:
	FILE* _fp;
	GImage* _tileMapBuffer;
	GImage* _tilesBuffer;
	Tile _selectTile;
	Tile _tileMap[5][100][100];
	Tile _tiles[20][20];
	POINT _cameraPos;
	char _tileSizeChar[20];
	bool _input;
	int _tileMapSize;
	int _layer;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MapToolScene() {}
	~MapToolScene() {}
};

