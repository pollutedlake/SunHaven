#pragma once
#include "../FrameWork/GameNode/GameNode.h"

struct inventoryList
{
	GImage* _imageInvenList;
	RECT _rc;
	bool _draw;
	int _category;
};

struct equipmentSlot
{
	GImage* _imageEquipmentSlot;
	RECT _rc;
	bool _draw;
	int _category;
};


class Inventory : public GameNode
{

private:
	RECT _invenBG;
	RECT _playerBG;
	RECT _playerName;
	RECT _itemListBG;
	RECT _trashButton;
	RECT _sortButton;
	RECT _dropButton;
	RECT _xButton;

	RECT _playerStat[5];

	DWORD _lastItemTime;
	int _getItem;
	int _selectedItem;

	vector<inventoryList> _vInvenList;
	vector<inventoryList>::iterator _viInvenList;

	vector<equipmentSlot> _vEquipmentSlot;
	vector<equipmentSlot>::iterator _viEquipmentSlot;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Inventory(){}
	~Inventory(){}
};

