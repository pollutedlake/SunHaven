#pragma once
#include "Object.h"

class Tree : public Object
{
public:
	HRESULT init(void);
	virtual HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void update(void);
	void render(void);
	void release(void);

	void setHP(int damage);

	Tree() {}
	~Tree() {}
};

