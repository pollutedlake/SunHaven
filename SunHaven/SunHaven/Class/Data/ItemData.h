#pragma once
#include "../Item/Item.h"

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
	/*void armorSetUp(Item* qItem = nullptr);
	void materialSetUp(Item* qItem = nullptr);
	void consumableSetUp(Item* qItem = nullptr);*/

	//queue<Item*>* getItem() { return &this->_item; }
	//queue<Item*>* getItem() { return &this->_item; }
	queue<tagTool*>* getTool() { return &this->_tool; }
	queue<tagWeapon*>* getWeapon() { return &this->_weapon; }
	queue<tagArmor*>* getArmor() { return &this->_armor; }
	queue<tagIngredient*>* getIngredient() { return &this->_ingredient; }
	queue<tagConsumable*>* getConsumable() { return &this->_consumable; }

	ItemData() {}
	~ItemData() {}
};

