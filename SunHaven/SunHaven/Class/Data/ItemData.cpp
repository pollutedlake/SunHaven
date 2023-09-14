#include "Stdafx.h"
#include "ItemData.h"

void ItemData::init(void)
{
	//itemSetUp();
	toolSetUp();
	weaponSetUp();
	armorSetUp();
	accessorySetUp();
	ingredientSetUp();
	consumableSetUp();
}

void ItemData::toolSetUp(tagTool* qTool)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Item.json");

	for (auto it = root["Item"]["Tool"].begin(); it != root["Item"]["Tool"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagTool* qTool = new tagTool;

			Json::Value arrStrType = (*it)["_strType"];
			vector<string> strType;
			for (int i = 0; i < arrStrType.size(); i++)
			{
				strType.push_back((*it)["_strType"][i].asString());
			}

			Json::Value arrIntType = (*it)["_intType"];
			int* intType = (int*)malloc(sizeof(int) * arrIntType.size());

			if (intType != nullptr)
			{
				for (int i = 0; i < arrIntType.size(); i++)
				{
					*(intType + i) = (*it)["_intType"][i].asInt();
				}
			}

			qTool->index = strType[0];
			qTool->filePath = strType[1];
			qTool->name = strType[2];
			qTool->type = strType[3];
			qTool->grade = strType[4];
			qTool->description = strType[5];
			qTool->ingredient = strType[6];
			qTool->ingredientNum = intType[0];
			qTool->minDamage = intType[1];
			qTool->maxDamage = intType[2];
			qTool->attackSpeed = intType[3];
			qTool->requireLv = intType[4];
			qTool->time = intType[5];
			//qTool->gold = intType[6];
			qTool->sellGold = intType[6];

			free(intType);
			_tool.push(qTool);
		}
	}
}

void ItemData::weaponSetUp(tagWeapon* qWeapon)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Item.json");

	for (auto it = root["Item"]["Weapon"].begin(); it != root["Item"]["Weapon"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagWeapon* qWeapon = new tagWeapon;
			//Item* qItem = new Item;

			Json::Value arrStrType = (*it)["_strType"];
			//string* strType = (string*)malloc(sizeof(string) * arrStrType.size());
			vector<string> strType;
			for (int i = 0; i < arrStrType.size(); i++)
			{
				strType.push_back((*it)["_strType"][i].asString());
			}

			Json::Value arrIntType = (*it)["_intType"];
			int* intType = (int*)malloc(sizeof(int) * arrIntType.size());

			if (intType != NULL)
			{
				for (int i = 0; i < arrIntType.size(); i++)
				{
					*(intType + i) = (*it)["_intType"][i].asInt();
				}
			}

			qWeapon->index = strType[0];
			qWeapon->filePath = strType[1];
			qWeapon->name = strType[2];
			qWeapon->type = strType[3];
			qWeapon->grade = strType[4];
			qWeapon->description = strType[5];
			qWeapon->ingredient = strType[6];
			qWeapon->ingredientNum = intType[0];
			qWeapon->minDamage = intType[1];
			qWeapon->maxDamage = intType[2];
			qWeapon->attackSpeed = intType[3];
			qWeapon->requireLv = intType[4];
			qWeapon->time = intType[5];
			qWeapon->gold = intType[6];
			qWeapon->sellGold = intType[7];

			free(intType);
			_weapon.push(qWeapon);
		}
	}
}

void ItemData::armorSetUp(tagArmor* qArmor)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Item.json");

	for (auto it = root["Item"]["Armor"].begin(); it != root["Item"]["Armor"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagArmor* qArmor = new tagArmor;

			Json::Value arrStrType = (*it)["_strType"];
			vector<string> strType;
			for (int i = 0; i < arrStrType.size(); i++)
			{
				strType.push_back((*it)["_strType"][i].asString());
			}

			Json::Value arrIntType = (*it)["_intType"];
			int* intType = (int*)malloc(sizeof(int) * arrIntType.size());

			if (intType != NULL)
			{
				for (int i = 0; i < arrIntType.size(); i++)
				{
					*(intType + i) = (*it)["_intType"][i].asInt();
				}
			}

			qArmor->index = strType[0];
			qArmor->filePath = strType[1];
			qArmor->name = strType[2];
			qArmor->type = strType[3];
			qArmor->grade = strType[4];
			qArmor->description = strType[5];
			qArmor->ingredient = strType[6];
			qArmor->ingredientNum = intType[0];
			qArmor->defense = intType[1];
			qArmor->maxHp = intType[2];
			qArmor->requireLv = intType[3];
			qArmor->time = intType[4];
			qArmor->gold = intType[5];
			qArmor->sellGold = intType[6];

			free(intType);
			_armor.push(qArmor);
		}
	}
}

void ItemData::accessorySetUp(tagAccessory* qAcc)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Item.json");

	for (auto it = root["Item"]["Accessory"].begin(); it != root["Item"]["Accessory"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagAccessory* qAcc = new tagAccessory;

			Json::Value arrStrType = (*it)["_strType"];
			vector<string> strType;
			for (int i = 0; i < arrStrType.size(); i++)
			{
				strType.push_back((*it)["_strType"][i].asString());
			}

			Json::Value arrIntType = (*it)["_intType"];
			int* intType = (int*)malloc(sizeof(int) * arrIntType.size());

			if (intType != NULL)
			{
				for (int i = 0; i < arrIntType.size(); i++)
				{
					*(intType + i) = (*it)["_intType"][i].asInt();
				}
			}

			qAcc->index = strType[0];
			qAcc->filePath = strType[1];
			qAcc->name = strType[2];
			qAcc->type = strType[3];
			qAcc->grade = strType[4];
			qAcc->description = strType[5];
			qAcc->ingredient = strType[6];
			qAcc->ingredientNum = intType[0];
			qAcc->attackDamage = intType[1];
			qAcc->spellDamage = intType[2];
			qAcc->requireLv = intType[3];
			qAcc->time = intType[4];
			qAcc->gold = intType[5];
			qAcc->sellGold = intType[6];

			free(intType);
			_acc.push(qAcc);
		}
	}
}

void ItemData::ingredientSetUp(tagIngredient* qIngredient)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Item.json");

	for (auto it = root["Item"]["Ingredient"].begin(); it != root["Item"]["Ingredient"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagIngredient* qIngredient = new tagIngredient;

			Json::Value arrStrType = (*it)["_strType"];
			vector<string> strType;
			for (int i = 0; i < arrStrType.size(); i++)
			{
				strType.push_back((*it)["_strType"][i].asString());
			}

			Json::Value arrIntType = (*it)["_intType"];
			int* intType = (int*)malloc(sizeof(int) * arrIntType.size());

			if (intType != NULL)
			{
				for (int i = 0; i < arrIntType.size(); i++)
				{
					*(intType + i) = (*it)["_intType"][i].asInt();
				}
			}

			qIngredient->index = strType[0];
			qIngredient->filePath = strType[1];
			qIngredient->name = strType[2];
			qIngredient->type = strType[3];
			qIngredient->description = strType[4];
			qIngredient->stackSize = intType[0];
			qIngredient->sellGold = intType[1];

			free(intType);
			_ingredient.push(qIngredient);
		}
	}
}

void ItemData::consumableSetUp(tagConsumable* qConsumable)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("./Schema/Item.json");

	for (auto it = root["Item"]["Consumable"].begin(); it != root["Item"]["Consumable"].end(); it++)
	{
		if ((*it).isObject())
		{
			tagConsumable* qConsumable = new tagConsumable;

			Json::Value arrStrType = (*it)["_strType"];
			vector<string> strType;
			for (int i = 0; i < arrStrType.size(); i++)
			{
				strType.push_back((*it)["_strType"][i].asString());
			}

			Json::Value arrIntType = (*it)["_intType"];
			int* intType = (int*)malloc(sizeof(int) * arrIntType.size());

			if (intType != NULL)
			{
				for (int i = 0; i < arrIntType.size(); i++)
				{
					*(intType + i) = (*it)["_intType"][i].asInt();
				}
			}

			qConsumable->index = strType[0];
			qConsumable->filePath = strType[1];
			qConsumable->name = strType[2];
			qConsumable->type = strType[3];
			qConsumable->description = strType[4];
			qConsumable->hp = intType[0];
			qConsumable->mp = intType[1];
			qConsumable->stackSize = intType[2];
			qConsumable->gold = intType[3];
			qConsumable->sellGold = intType[4];

			free(intType);
			_consumable.push(qConsumable);
		}
	}
}

void ItemData::getItem(string addItemName, string addItemArrIndex)
{
	
	
}
