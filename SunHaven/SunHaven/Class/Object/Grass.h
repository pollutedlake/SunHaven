#pragma once
#include "Object.h"

class Grass : public Object
{
public:
	HRESULT init(void);
	virtual HRESULT init(LivingObjectType type, POINT tilePos = { NULL, NULL });
	void release(void);
	void update(void);
	void render(void);

	Grass() {}
	~Grass() {}
};

