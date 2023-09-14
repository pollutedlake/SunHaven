#pragma once
#include "Object.h"

class Tree : public Object
{
private:
	float _hitTime;
	RECT _beforeHitRC;
	RECT _hitRC;
	RECT _cutTreeRC;
	bool _hit;
	GPImage* _cutTreeImg;
	float _cutTreeAngle;
	bool _fell;
	bool _fellLeft;

public:
	HRESULT init(void);
	virtual HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void update(void);
	void render(void);
	void release(void);

	void setHP(int damage, float playerX = NULL);

	Tree() {}
	~Tree() {}
};

