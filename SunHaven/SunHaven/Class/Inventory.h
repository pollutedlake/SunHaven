#pragma once
#include "../FrameWork/GameNode/GameNode.h"

struct Slot
{
	
	RECT _rc;
	bool _draw;
	string _category;
	int _currentStack;
	

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
	
	bool _inInvenSlot;
	bool _inEquipmentSlot;
	

	vector<Slot> _vInvenList;
	vector<Slot>::iterator _viInvenList;

	vector<Slot> _vEquipmentSlot;
	vector<Slot>::iterator _viEquipmentSlot;

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
	void putItem();
	void invenXButton();

	//vector<tagWeapon*> getWeapon() { return _vWeapon; }
	//
	//vector<tagAccessory*> getAccessory() { return _vAccessory; }
	//
	//vector<tagConsumable*> getConsumable() { return _vConsumable; }
	

	Inventory(){}
	~Inventory(){}
};

