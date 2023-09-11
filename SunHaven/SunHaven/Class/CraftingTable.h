#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class CraftingTable : public GameNode
{
private:
	RECT _bg;
	RECT _queueBg;
	RECT _filterBg;
	RECT _cancelButton;
	RECT _banner;
	RECT _rightBanner;
	RECT _searchBg;
	RECT _xButton;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

