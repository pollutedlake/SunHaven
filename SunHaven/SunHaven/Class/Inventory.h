#pragma once
#include "../FrameWork/GameNode/GameNode.h"

struct inventoryList
{
	GImage* _invenList;
	RECT _rc;
};


class Inventory : public GameNode
{

private:
	RECT _invenBG;
	RECT _playerBG;
	RECT _playerName;
	RECT _itemListBG;

	vector<inventoryList> _vInvenList;
	vector<inventoryList>::iterator _viInvenList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Inventory(){}
	~Inventory(){}
};

