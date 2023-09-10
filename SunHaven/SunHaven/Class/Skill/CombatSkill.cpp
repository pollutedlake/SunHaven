#include "Stdafx.h"
#include "CombatSkill.h"

void CombatSkill::init(string index, string name, string type, int tier, string description,
		double value1[], double value2[])
{
	_index = index;
	_type = type;
	_tier = tier;
	_description = description;

	for (int i = 0; i < 3; i++)
	{
		_value1[i] = value1[i];
		_value2[i] = value2[i];
	}
}
