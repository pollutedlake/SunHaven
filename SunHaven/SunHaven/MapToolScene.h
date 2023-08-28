#pragma once
#include "GameNode.h"

struct Tile
{
	GImage* _image;
};

class MapToolScene : public GameNode
{
private:
	GImage* _tileBuffer;
	Tile _tileMap[100][100];
	POINT _cameraPos;
	char _tileSizeChar[20];
	bool _input;
	int _tileMapSize;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MapToolScene() {}
	~MapToolScene() {}
};

