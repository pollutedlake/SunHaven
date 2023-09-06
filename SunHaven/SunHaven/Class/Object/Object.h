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
	RECT _collisionRC;
	RECT _transParentRC;
	int _offsetX;
	int _offsetY;
	float _cx, _cy;
	int HP;

public:
	HRESULT init(void);
	HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void release(void);
	void update(void);
	void render(void);
	void render(HDC hdc);

	void halfTransRender();
	void updateCameraPos(float cx, float cy);
	void renderToPoint(POINT point);
	void setTilePos(POINT tilePos) {_tilePos = tilePos;}

	POINT getTilePos() {return _tilePos;}
	LivingObjectType getType() {return _type;}
	RECT getCollisionRC() {return _collisionRC;}
	RECT getTransParentRC() {return _transParentRC;}

	Object() {}
	~Object() {}
};

