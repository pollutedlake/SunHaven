#pragma once
#include "Skill.h"

class MiningSkill : public Skill
{
private:
	skillImg _img;
	skillBorderImg _borderImg[40];
	char str[50];


	bool _isDescription = false;

public:
	void init(string index, string name, string type, int tier, string description, double value1[], double value2[]);

	HRESULT init();
	void release();
	void update();
	void render();

	MiningSkill() {}
	~MiningSkill() {}
};

