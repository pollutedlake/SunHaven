#pragma once
#include "../FrameWork/GameNode/GameNode.h"

struct inventoryList
{
	
	RECT _rc;
	bool _draw;
	string _category;

};

struct equipmentSlot
{
	
	RECT _rc;
	bool _draw;
	string _category;
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
	string _getItem;
	int _selectedItem;

	bool _seeInven;
	

	vector<inventoryList> _vInvenList;
	vector<inventoryList>::iterator _viInvenList;

	vector<equipmentSlot> _vEquipmentSlot;
	vector<equipmentSlot>::iterator _viEquipmentSlot;

	/*vector<tagTool*> _vTool;
	vector<tagTool*>::iterator _viTool;

	vector<tagWeapon*> _vWeapon;
	vector<tagWeapon*>::iterator _viWeapon;

	vector<tagAccessory*> _vAccessory;
	vector<tagAccessory*>::iterator _viAccessory;

	vector<tagConsumable*> _vConsumable;
	vector<tagConsumable*>::iterator _viConsumable;

	vector<tagArmor*> _vArmor;
	vector<tagArmor*>::iterator _viArmor;

	vector<tagIngredient*> _vIngredient;
	vector<tagIngredient*>::iterator _viIngredient;*/

	

	
	


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	//void getItem();
	void getItem(string index);
	void itemMove();
	void invenMold();
	void invenSlot();
	void equipment_Slot();
	void moveItemRender();
	void popupItem();

	//vector<tagWeapon*> getWeapon() { return _vWeapon; }
	//
	//vector<tagAccessory*> getAccessory() { return _vAccessory; }
	//
	//vector<tagConsumable*> getConsumable() { return _vConsumable; }
	

	Inventory(){}
	~Inventory(){}
};

