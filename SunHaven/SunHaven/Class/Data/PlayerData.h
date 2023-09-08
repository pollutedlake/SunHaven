#pragma once
#include "../Skill/Skill.h"

class PlayerData
{
private:
	queue<Skill*> _skill;

public:
	void init(void);
	void explorationSetUp(Skill* qExplor = nullptr);
	void farmingSetUp(Skill* qFarm = nullptr);
	void miningSetUp(Skill* qMine = nullptr);
	void combatSetUp(Skill* qCombat = nullptr);
	void fishingSetUp(Skill* qFish = nullptr);

	queue<Skill*>* getSkill() { return &this->_skill; }

	PlayerData() {}
	~PlayerData() {}
};

