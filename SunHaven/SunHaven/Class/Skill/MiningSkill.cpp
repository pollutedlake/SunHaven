#include "Stdafx.h"
#include "MiningSkill.h"

void MiningSkill::init(string index, string name, string type, int tier, string description, float value1[], float value2[], const char* filePath, int width, int height)
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

	_filePath = filePath;
}
