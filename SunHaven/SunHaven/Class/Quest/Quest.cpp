#include "Stdafx.h"
#include "Quest.h"

void Quest::init(string name, int exp, string description, string item, int monster, string questCheck, int gold, string monsterName, string questPlace)
{
    _name = name;
    _gold = gold;
    _exp = exp;
    _description = description;
    _item = item;
    _monster = monster;  // 순서 변경
    _questCheck = questCheck;
    _monsterName = monsterName;
    _questPlace = questPlace;
}
