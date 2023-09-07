#pragma once
#include "Skill.h"
class CombatSkill :
    public Skill
{
private:


public:
    void init(string index, string name, string type, int tier, string description,
        float value1[], float value2[], const char* filePath, int width, int height);
};

