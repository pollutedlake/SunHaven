#pragma once
#include "Object.h"

class Rock : public Object
{
private:
	float _hitTime;
	RECT _beforeHitRC;
	RECT _hitRC;
	bool _hit;

public:
	HRESULT init(void);
	virtual HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void release(void);
	void update(void);
	void render(void);

	void setHP(int damage, float playerX = NULL);
	Rock() {}
	~Rock() {}
};

