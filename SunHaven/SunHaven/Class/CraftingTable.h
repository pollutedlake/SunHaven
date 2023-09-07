#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class CraftingTable : public GameNode
{
private:
	RECT _bg;
	RECT _queueBg;
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

