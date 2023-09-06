#pragma once
#include "Object.h"

class Grass : public Object
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Grass() {}
	~Grass() {}
};

