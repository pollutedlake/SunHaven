#pragma once
#include "../../FrameWork/GameNode/GameNode.h"

enum LivingObjectType
{
	GRASS1,
	GRASS2,
	TREE1,
	TREE2,
	STONE1,
	STONE2
};

class Object : public GameNode
{
private:
	GImage* _image;
	POINT _tilePos;
	LivingObjectType _type;
	RECT _rc;
	int _offsetX;
	int _offsetY;

public:
	HRESULT init(void);
	HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void release(void);
	void update(void);
	void render(void);
	void render(HDC hdc);

	void renderToMouse();
	void setTilePos(POINT tilePos) {_tilePos = tilePos;}
	POINT getTilePos() {return _tilePos;}
	LivingObjectType getType() {return _type;}

	Object() {}
	~Object() {}
};

