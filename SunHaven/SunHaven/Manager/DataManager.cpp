#include "Stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init(void)
{
	itemData.init();
	while (!itemData.getTool()->empty())
	{
		_vTool.push_back(itemData.getTool()->front());
		itemData.getTool()->pop();
	}
	while (!itemData.getArmor()->empty())
	{
		_vArmor.push_back(itemData.getArmor()->front());
		itemData.getArmor()->pop();
	}
	while (!itemData.getConsumable()->empty())
	{
		_vConsumable.push_back(itemData.getConsumable()->front());
		itemData.getConsumable()->pop();
	}
	while (!itemData.getIngredient()->empty())
	{
		_vIngredient.push_back(itemData.getIngredient()->front());
		itemData.getIngredient()->pop();
	}
	while (!itemData.getWeapon()->empty())
	{
		_vWeapon.push_back(itemData.getWeapon()->front());
		itemData.getWeapon()->pop();
	}
	while (!itemData.getAccessory()->empty())
	{
		_vAcc.push_back(itemData.getAccessory()->front());
		itemData.getAccessory()->pop();
	}
	return S_OK;
}

void DataManager::release(void)
{
	for (auto it = _vArmor.begin(); it != _vArmor.end();)
	{
		SAFE_DELETE(*it);
		(*it) = nullptr;
		it = _vArmor.erase(it);
	}
	for (auto it = _vTool.begin(); it != _vTool.end();)
	{
		SAFE_DELETE(*it);
		(*it) = nullptr;
		it = _vTool.erase(it);
	}
	for (auto it = _vConsumable.begin(); it != _vConsumable.end();)
	{
		SAFE_DELETE(*it);
		(*it) = nullptr;
		it = _vConsumable.erase(it);
	}
	for (auto it = _vIngredient.begin(); it != _vIngredient.end();)
	{
		SAFE_DELETE(*it);
		(*it) = nullptr;
		it = _vIngredient.erase(it);
	}
	for (auto it = _vWeapon.begin(); it != _vWeapon.end();)
	{
		SAFE_DELETE(*it);
		(*it) = nullptr;
		it = _vWeapon.erase(it);
	}
	for (auto it = _vArmor.begin(); it != _vArmor.end();)
	{
		SAFE_DELETE(*it);
		(*it) = nullptr;
		it = _vArmor.erase(it);
	}
}

tagTool* DataManager::getToolInfo(int index)
{
	return _vTool[index];
}

tagWeapon* DataManager::getWeaponInfo(int index)
{
	return _vWeapon[index];
}

tagArmor* DataManager::getArmorInfo(int index)
{
	return _vArmor[index];
}

tagAccessory* DataManager::getAccessoryInfo(int index)
{
	return _vAcc[index];
}

tagIngredient* DataManager::getIngredientInfo(int index)
{
	return _vIngredient[index];
}

tagConsumable* DataManager::getConsumableInfo(int index)
{
	return _vConsumable[index];
}
