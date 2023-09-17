#include "Stdafx.h"
#include "EnemyManager.h"
#include "Shadeclaw.h"
#include "Rootwalker.h"
#include "SteelSlug.h"
#include "FlameImp.h"
#include "../../Player/Player.h"

HRESULT EnemyManager::init(void)
{

	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();

		SAFE_DELETE(*_viEnemy);
	}
}

void EnemyManager::update(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->setPlayerX(_player->getPlayerPosition().x);
		(*_viEnemy)->setPlayerY(_player->getPlayerPosition().y);
		(*_viEnemy)->update();
	}
}

void EnemyManager::render(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}

void EnemyManager::spawnSteelSlug(void)
{
	for (int i = 0; i < 2; i++)
	{
		
			Enemy* slug;
			slug = new SteelSlug;
			slug->init(PointMake(600 + i * 950, 800));
			_vEnemy.push_back(slug);
		
	}
}

void EnemyManager::spawnFlameImp(void)
{
	for (int i = 0; i < 2; i++)
	{
		
			Enemy* flameImp;
			flameImp = new FlameImp;
			flameImp->init(PointMake(1200 + i * 1200, 850 ));
			_vEnemy.push_back(flameImp);
		
	}
}

void EnemyManager::spawnShadeclaw(void)
{
	for (int i = 0; i < 2; i++)
	{
		Enemy* shadeclaw;
		shadeclaw = new Shadeclaw;
		shadeclaw->init(PointMake(650 + i * 100, 350));
		_vEnemy.push_back(shadeclaw);
	}
}

void EnemyManager::spawnRootwalker(void)
{
	for (int i = 0; i < 2; i++)
	{
		Enemy* rootwalker;
		rootwalker = new Rootwalker;
		rootwalker->init(PointMake(650 + i * 100, 350));
		_vEnemy.push_back(rootwalker);
	}
}

void EnemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}