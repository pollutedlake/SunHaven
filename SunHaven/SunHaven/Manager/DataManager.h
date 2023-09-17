#pragma once
#include "../FrameWork/SingletonBase/SingletonBase.h"
#include "../Class/Data/ItemData.h"

struct tagPlayerState
{
	char* playerName;
	float playerSpeed;
	int HP;
	int MP;
	int MaxHP;
	int MaxMP;
	float HPRecoveryPerSec;
	float MPRecoveryPerSec;
	int gold;

	int attackDamage;
	int spellDamage;
	int defence;
	float critical;

	int mineEXP;
	int combatEXP;
	int farmingEXP;
};

struct Slot
{

	RECT _rc;
	bool _draw;
	string _category;
	int _currentStack;
};

class DataManager : public SingletonBase<DataManager>
{
private:
	ItemData itemData;
	vector<tagTool*> _vTool;
	vector<tagWeapon*> _vWeapon;
	vector<tagArmor*> _vArmor;
	vector<tagAccessory*> _vAcc;
	vector<tagIngredient*> _vIngredient;
	vector<tagConsumable*> _vConsumable;

	tagPlayerState _playerState;
	vector<Slot> _vInvenList;
	vector<Slot>::iterator _viInvenList;

	vector<Slot> _vEquipmentSlot;
	vector<Slot>::iterator _viEquipmentSlot;

public:
	HRESULT init(void);
	void release(void);
	
	tagTool* getToolInfo(int index);
	tagWeapon* getWeaponInfo(int index);
	tagArmor* getArmorInfo(int index);
	tagAccessory* getAccessoryInfo(int index);
	tagIngredient* getIngredientInfo(int index);
	tagConsumable* getConsumableInfo(int index);

	void setData(tagPlayerState playerState, vector<Slot>* vInvenList = nullptr, vector<Slot>* vEquipmentSlot = nullptr);
	vector<Slot> getInvenList() {return _vInvenList;}
	vector<Slot> getEquipmentList() {return _vEquipmentSlot;}
	tagPlayerState getPlayereState() {return _playerState;}

	DataManager() {}
	~DataManager() {}

};

