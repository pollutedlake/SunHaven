#include "Stdafx.h"
#include "SkillManager.h"

SkillManager::SkillManager():
			_currentSkill(nullptr)
{
}


HRESULT SkillManager::init(void)
{
	_combat = new CombatSkill;
	_combat->init();

	_mining = new MiningSkill;
	_mining->init();

	_fishing = new FishingSkill;
	_fishing->init();

	_farming = new FarmingSkill;
	_farming->init();

	_exploration = new ExplorationSkill;
	_exploration->init();


	_currentSkill = _mining;

	return S_OK;
}

void SkillManager::release(void)
{
	_combat->release();
	SAFE_DELETE(_combat);
	
	_mining->release();
	SAFE_DELETE(_mining);
	
	_fishing->release();
	SAFE_DELETE(_fishing);
	
	_farming->release();
	SAFE_DELETE(_farming);
	
	_exploration->release();
	SAFE_DELETE(_exploration);
}

void SkillManager::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_currentSkill = _combat;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_currentSkill = _mining;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_currentSkill = _fishing;
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_currentSkill = _farming;
	}
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		_currentSkill = _exploration;
	}


	_currentSkill->update();
}

void SkillManager::render(void)
{
	_currentSkill->render();
}
