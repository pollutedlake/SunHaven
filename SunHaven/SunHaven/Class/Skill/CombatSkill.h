#pragma once
#include "Skill.h"
class CombatSkill :
    public Skill
{
private:


public:
	void init(string index, string name, string type, int tier, string description,
		double value1[], double value2[]);
};

