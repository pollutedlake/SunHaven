#pragma once

struct tagQuest
{

};

class Quest
{
protected:
	int _exp;
	int _gold;
	int _monster;

	string _name;
	string _description;
	string _item;
	string _questCheck;
	string _monsterName;
	string _questPlace;

public:
	void init(string name, int exp, string description, string item, int monster,
		string questCheck, int gold, string monsterName, string questPlace);


	int getGold() { return this->_gold; }
	int getExp() { return this->_exp; }
	int getMonster() { return this->_monster; }

	string getName() { return this->_name; }
	string getDescription() { return this->_description; }
	string getItem() { return this->_item; }
	string getQuestCheck() { return this->_questCheck; }
	string getMonsterName() { return this->_monsterName; }
	string getQuestPlace() { return this->_questPlace; }

	Quest() {}
	~Quest() {}

};

