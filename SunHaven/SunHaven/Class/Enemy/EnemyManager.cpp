#include "stdafx.h"
#include "EnemyManager.h"
//#include "Enemy.h"
//#include "Enemy2.h"
//#include "Enemy3.h"
//#include "Rocket.h"

HRESULT EnemyManager::init(void)
{
	setEnemy();

	_bullet = new Bullet;
	_bullet->init("적 미사일", 30, 1000);

	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();

		SAFE_DELETE(*_viEnemy);
	}

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void EnemyManager::update(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}

	EnemyBulletFire();
	_bullet->update();
	collision();
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
	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Enemy;
			jellyFish->init("해파리", PointMake(250 + j * 200, i * 100));
			_vEnemy.push_back(jellyFish);
		}
	}

	for (int i = 0; i < 15; i++)
	{
		Enemy* jellyFish;
		jellyFish = new Enemy2;
		jellyFish->init("해파리", PointMake(CENTER_X + 150 * cos(DEGREE_RADIAN(24 * i)), CENTER_Y + 150 * sin(DEGREE_RADIAN(24 * i))));
		_vEnemy.push_back(jellyFish);
	}

	for (int i = 0; i < 15; i++)
	{
		Enemy* jellyFish;
		jellyFish = new Enemy3;
		jellyFish->init("해파리", PointMake(CENTER_X + 600 * cos(DEGREE_RADIAN(12 * i)), CENTER_Y - 700 + 600 * sin(DEGREE_RADIAN(12 * i))));
		_vEnemy.push_back(jellyFish);
	}*/
}

void EnemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

void EnemyManager::EnemyBulletFire(void)
{
	//for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	//{
	//	if ((*_viEnemy)->bulletCountFire())	// 우선 참조
	//	{
	//		RECT rc = (*_viEnemy)->getRect();

	//		_bullet->fire(rc.left + (rc.right - rc.left) / 2,
	//			rc.bottom + (rc.top - rc.bottom) / 2 + 30,
	//			getAngle(rc.left + (rc.right - rc.left) / 2,
	//				rc.bottom + (rc.top - rc.bottom) / 2,
	//				_rocket->getPosition().x,
	//				_rocket->getPosition().y),
	//			RND->getFromFloatTo(2.0f, 4.0f));
	//	}
	//}
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
