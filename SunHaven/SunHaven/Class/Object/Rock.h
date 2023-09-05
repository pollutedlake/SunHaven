#pragma once
#include "Object.h"

class Rock : public Object
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Rock() {}
	~Rock() {}
};

