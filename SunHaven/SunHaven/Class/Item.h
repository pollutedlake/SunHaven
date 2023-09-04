#pragma once
#include "../FrameWork/GameNode/GameNode.h"

struct itemp 
{

	int Value;

};


class Item : public GameNode
{

private:


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Item(){}
	~Item(){}
};

