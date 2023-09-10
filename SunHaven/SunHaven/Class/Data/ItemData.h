#pragma once
#include "../Item/Item.h"

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

class ItemData
{
private:
	//queue<Item*> _item;
	queue<tagTool*> _tool;
	queue<tagWeapon*> _weapon;
	queue<tagArmor*> _armor;
	queue<tagAccessory*> _acc;
	queue<tagIngredient*> _ingredient;
	queue<tagConsumable*> _consumable;


public:
	void init(void);
	//void itemSetUp(Item* qItem = nullptr);
	void toolSetUp(tagTool* qTool = nullptr);
	void weaponSetUp(tagWeapon* qWeapon = nullptr);
	void armorSetUp(tagArmor* qArmor = nullptr);
	void accessorySetUp(tagAccessory* qAcc = nullptr);
	void ingredientSetUp(tagIngredient* qIngredient = nullptr);
	void consumableSetUp(tagConsumable* qConsumable = nullptr);
	
	queue<tagTool*>* getTool() { return &this->_tool; }
	queue<tagWeapon*>* getWeapon() { return &this->_weapon; }
	queue<tagArmor*>* getArmor() { return &this->_armor; }
	queue<tagIngredient*>* getIngredient() { return &this->_ingredient; }
	queue<tagConsumable*>* getConsumable() { return &this->_consumable; }

	ItemData() {}
	~ItemData() {}
};

