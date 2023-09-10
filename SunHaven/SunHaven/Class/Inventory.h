#pragma once
#include "../FrameWork/GameNode/GameNode.h"
#include "../Class/Data/ItemData.h"

struct inventoryList
{
	
	RECT _rc;
	bool _draw;
	int _category;

};

struct equipmentSlot
{
	
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

	vector<tagTool*> _vTool;
	vector<tagTool*>::iterator _viTool;

	ItemData* _ID;
	


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void getItem();
	void itemMove();
	void invenMold();
	void invenSlot();
	void equipment_Slot();
	void moveItemRender();
	void popupItem();

	Inventory(){}
	~Inventory(){}
};

