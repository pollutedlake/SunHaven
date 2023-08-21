#pragma once
#include "GameNode.h"

struct Tile
{
	GImage* _image;
};

class MapToolScene : public GameNode
{
private:
	Tile _tileMap[100][100];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MapToolScene() {}
	~MapToolScene() {}
};

