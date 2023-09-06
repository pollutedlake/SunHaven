#pragma once
#include "Object.h"

class Tree : public Object
{
public:
	HRESULT init(void);
	void update(void);
	void render(void);
	void release(void);

	Tree() {}
	~Tree() {}
};

