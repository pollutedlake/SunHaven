#pragma once
#include "Item.h"
class Weapon : public Item
{
private:
	string _name;

public:
	HRESULT init(string name, string category, string grade, int lowDamage, int highDamage,
		int attackSpeed, int gold, int sellGold);

	string getName(void) { return _name; }
};

