#pragma once
#include "../../FrameWork/GameNode/GameNode.h"
#include "CombatSkill.h"
#include "MiningSkill.h"
#include "FishingSkill.h"
#include "FarmingSkill.h"
#include "ExplorationSkill.h"

class SkillManager : public GameNode
{
private:
    Skill* _currentSkill;

    CombatSkill*        _combat;
    MiningSkill*        _mining;
    FishingSkill*       _fishing;
    FarmingSkill*       _farming;
    ExplorationSkill*   _exploration;

public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

    SkillManager();
    ~SkillManager() {}
};

