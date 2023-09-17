#include "Stdafx.h"
#include "EnemyManager.h"
#include "Shadeclaw.h"
#include "Rootwalker.h"
#include "SteelSlug.h"
#include "FlameImp.h"
#include "../../Player/Player.h"

HRESULT EnemyManager::init(void)
{
	setEnemy();

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

	//collision();
}

void EnemyManager::render(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}

void EnemyManager::setEnemy(void)
{

}

void EnemyManager::spawnSteelSlug(void)
{
	Enemy* slug;
	slug = new SteelSlug;
	slug->init(PointMake(600, 800));
	_vEnemy.push_back(slug);
}

void EnemyManager::spawnFlameImp(void)
{
	Enemy* flameImp;
	flameImp = new FlameImp;
	flameImp->init(PointMake(1000, 800));
	_vEnemy.push_back(flameImp);
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

void EnemyManager::collision(void)
{
	/*for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		for (int i = 0; i < (*_viEnemy)->getFireBall()->getBullet().size(); i++)
		{
			RECT rc;

			if (IntersectRect(&rc, &CollisionAreaResizing((*_viEnemy)->getFireBall()->getBullet()[i].rc, 21, 18),
				&_player->getPlayerRC()))
			{
				(*_viEnemy)->getFireBall()->removeBullet(i);
				_player->hitDamage(2.0f);
			}
		}
	}*/
}