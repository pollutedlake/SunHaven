#include "stdafx.h"
#include "EnemyManager.h"
#include "Shadeclaw.h"
#include "SteelSlug.h"
#include "FlameImp.h"
#include "../../Player/Player.h"

HRESULT EnemyManager::init(void)
{
	setEnemy();

	/*_bullet = new Bullet;

	_bullet->init("bullet", 100, 1000.0f);*/

	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();

		SAFE_DELETE(*_viEnemy);
	}

	//_bullet->release();
	//SAFE_DELETE(_bullet);
}

void EnemyManager::update(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->setPlayerX(_player->getPlayerPosition().x);
		(*_viEnemy)->setPlayerY(_player->getPlayerPosition().y);
		(*_viEnemy)->update();
	}

	//EnemyBulletFire();
	//_bullet->update();
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
		shadeclaw->init(PointMake(500 + i * 100, 300));
		_vEnemy.push_back(shadeclaw);
	}
}

void EnemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

void EnemyManager::EnemyBulletFire(void)
{
	/*for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		
			RECT rc = (*_viEnemy)->getRect();

			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2,
					_player->getPlayerPosition().x,
					_player->getPlayerPosition().y),
				RND->getFromFloatTo(2.0f, 4.0f));
		
	}*/
}

void EnemyManager::collision(void)
{
	/*for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;

		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc, &_rocket->getRect()))
		{
			_bullet->removeBullet(i);
			_rocket->hitDamage(2.0f);
		}
	}*/
}
