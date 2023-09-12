#pragma once
#include "../../FrameWork/GameNode/GameNode.h"
#include "../UI/ProgressBar.h"

enum LivingObjectType
{
	GRASS1,
	GRASS2,
	TREE1,
	TREE2,
	ROCK1,
	ROCK2
};

class Object : public GameNode
{
protected:
	queue<string> _dropItemList;
	ProgressBar* _hpBar;
	GImage* _image;
	POINT _tilePos;
	LivingObjectType _type;
	RECT _collisionRC;
	bool _halfTrans;
	RECT _rc;
	int _offsetX;
	int _offsetY;
	float _cx, _cy;
	int _hpBarOffsetX;
	int _hpBarOffsetY;
	int _maxHp;
	int _curHp;

public:
	HRESULT init(void);
	virtual HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void release(void);
	void update(void);
	void render(void);
	void render(HDC hdc);
	void renderToPoint(POINT point);
	void renderHpBar();

	void updateCameraPos(float cx, float cy);
	void setTilePos(POINT tilePos) {_tilePos = tilePos;}
	void setHalfTrans(bool halfTrans) { _halfTrans = halfTrans; }

	POINT getTilePos() {return _tilePos;}
	LivingObjectType getType() {return _type;}
	RECT getCollisionRC() {return _collisionRC;}
	RECT getRC() {return _rc;}

	virtual void setHP(int damage);
	int getCurHP() {return _curHp;}

	void dropItem();

	Object() {}
	~Object() {}
};

