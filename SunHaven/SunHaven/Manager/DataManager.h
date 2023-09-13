#pragma once
#include "../FrameWork/SingletonBase/SingletonBase.h"
#include "../Class/Data/ItemData.h"

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

public:
	HRESULT init(void);
	void release(void);
	
	tagTool* getToolInfo(int index);
	tagWeapon* getWeaponInfo(int index);
	tagArmor* getArmorInfo(int index);
	tagAccessory* getAccessoryInfo(int index);
	tagIngredient* getIngredientInfo(int index);
	tagConsumable* getConsumableInfo(int index);

	DataManager() {}
	~DataManager() {}

};

