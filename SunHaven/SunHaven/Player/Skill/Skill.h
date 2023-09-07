#pragma once
#include "../../FrameWork/GameNode/GameNode.h"

enum class eSkillType
{
	ADVENTURE=1,
	FARMING,
	MINING,
	COMBAT,
	FISHING
};

class Skill : public GameNode
{
private:
	int _totalSkillPoint;

protected:
	GImage* _skillImg[40];
	GImage* _skillFrameImg[40];

	int _skillLv;
	int _skillTier;

	eSkillType _skillType;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Skill() {}
	~Skill() {}
};

