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
protected:
	GImage* _image;
	POINT _tilePos;
	LivingObjectType _type;
	RECT _collisionRC;
	bool _halfTrans;
	RECT _rc;
	int _offsetX;
	int _offsetY;
	float _cx, _cy;
	int HP;

public:
	HRESULT init(void);
	virtual HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void release(void);
	void update(void);
	void render(void);
	void render(HDC hdc);

	void updateCameraPos(float cx, float cy);
	void renderToPoint(POINT point);
	void setTilePos(POINT tilePos) {_tilePos = tilePos;}
	void setHalfTrans(bool halfTrans) { _halfTrans = halfTrans; }

	POINT getTilePos() {return _tilePos;}
	LivingObjectType getType() {return _type;}
	RECT getCollisionRC() {return _collisionRC;}
	RECT getRC() {return _rc;}

	Object() {}
	~Object() {}
};

