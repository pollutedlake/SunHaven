#pragma once
#include "Skill.h"
class FarmingSkill :
    public Skill
{
private:


public:
    void init(string index, string name, string type, int tier, string description,
        double value1[], double value2[]);
};

