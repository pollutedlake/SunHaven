#include "Stdafx.h"
#include "Weapon.h"

HRESULT Weapon::init(string name, string category, string grade, int lowDamage, int highDamage, int attackSpeed, int gold, int sellGold)
{
	_name = name;

	return S_OK;
}
