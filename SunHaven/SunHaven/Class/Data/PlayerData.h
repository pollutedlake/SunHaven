#pragma once

struct tagSkill
{
	string index;
	string name;
	string type;
	int tier;
	string description;
	double value1[3];
	double value2[3];
};

class PlayerData
{
private:
	queue<tagSkill*> _explor;
	queue<tagSkill*> _farm;
	queue<tagSkill*> _mine;
	queue<tagSkill*> _combat;
	queue<tagSkill*> _fish;

public:
	void init(void);
	void explorationSetUp(tagSkill* qExplor = nullptr);
	void farmingSetUp(tagSkill* qFarm = nullptr);
	void miningSetUp(tagSkill* qMine = nullptr);
	void combatSetUp(tagSkill* qCombat = nullptr);
	void fishingSetUp(tagSkill* qFish = nullptr);

	queue<tagSkill*>* getExplor() { return &this->_explor; }
	queue<tagSkill*>* getFarm() { return &this->_farm; }
	queue<tagSkill*>* getMine() { return &this->_mine; }
	queue<tagSkill*>* getCombat() { return &this->_combat; }
	queue<tagSkill*>* getFish() { return &this->_fish; }

	PlayerData() {}
	~PlayerData() {}
};

