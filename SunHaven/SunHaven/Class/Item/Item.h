#pragma once
//#include "../../FrameWork/GameNode/GameNode.h"

enum class EItemType
{
	TOOL,
	WEAPON,
	ARMOR,
	MATERIAL,
	CONSUMABLE
};

struct tagTool
{
	string index;
	string filePath;
	string name;
	string type;
	string grade;
	string description;
	string ingredient;
	int ingredientNum;
	int minDamage;
	int maxDamage;
	int attackSpeed;
	int requireLv;
	int time;
	int gold;
	int sellGold;
};

struct tagWeapon
{
	string index;
	string filePath;
	string name;
	string type;
	string grade;
	string description;
	string ingredient;
	int ingredientNum;
	int minDamage;
	int maxDamage;
	int attackSpeed;
	int requireLv;
	int time;
	int gold;
	int sellGold;
};

struct tagArmor
{
	string index;
	string filePath;
	string name;
	string type;
	string grade;
	string description;
	string ingredient;
	int ingredientNum;
	int defense;
	int maxHp;
	int requireLv;
	int time;
	int gold;
	int sellGold;
};

struct tagAccessory
{
	string index;
	string filePath;
	string name;
	string type;
	string grade;
	string description;
	string ingredient;
	int ingredientNum;
	int attackDamage;
	int spellDamage;
	int requireLv;
	int time;
	int gold;
	int sellGold;
};

struct tagIngredient
{
	string index;
	string filePath;
	string name;
	string type;
	string description;
	int stackSize;
	int sellGold;
};

struct tagConsumable
{
	string index;
	string filePath;
	string name;
	string type;
	string description;
	int hp;
	int mp;
	int stackSize;
	int gold;
	int sellGold;
};


class Item
{
private:



public:
	//void init()

	Item() {}
	~Item() {}
};

