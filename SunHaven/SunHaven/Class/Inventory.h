#pragma once
#include "../FrameWork/GameNode/GameNode.h"

class Player;

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
	Player* _player;

	DWORD _lastItemTime;
	string _getItem;
	int _selectedItem;

	bool _seeInven;
	
	bool _inInvenSlot;
	bool _inEquipmentSlot;
	
	int maxEquipmentRender;

	int _sellGold;
	int _att;
	int _def;
	int _hp;

	int _defIndex[5];

	vector<Slot> _vInvenList;
	vector<Slot>::iterator _viInvenList;

	vector<Slot> _vEquipmentSlot;
	vector<Slot>::iterator _viEquipmentSlot;

	vector<Slot> _vItemUseSlot;
	vector<Slot>::iterator _viItemUseSlot;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getItem(string index);
	void itemMove();
	void invenMold();
	void invenSlot();
	void equipment_Slot();
	void moveItemRender();
	void popupItem();
	void putItem();
	void invenXButton();
	void setCurrentSlot();
	void itemInfoPopup(int index);
	void sellItem();
	int getSellGold() { return _sellGold; }
	int getAtt() { return _att; }
	int getDef() { return _def; }
	int getHP() { return _hp; }

	RECT getPlayerStatSlot1() { return _playerStat[0]; }
	RECT getPlayerStatSlot2() { return _playerStat[1]; }
	RECT getPlayerStatSlot3() { return _playerStat[2]; }
	RECT getPlayerStatSlot4() { return _playerStat[3]; }
	RECT getPlayerStatSlot5() { return _playerStat[4]; }
	void setPlayerAdsress(Player* player) {_player = player; }
	bool getSeeInven() { return _seeInven; }

	vector<Slot>* getInvenList() { return &_vInvenList; }
	vector<Slot>* getEquipmentList() { return &_vEquipmentSlot; }
	void setInvenList(vector<Slot> vInvenList) { _vInvenList = vInvenList; }
	void setEuqipmentList(vector<Slot> vEquipmentList) { _vEquipmentSlot = vEquipmentList; }

	Inventory(){}
	~Inventory(){}
};

