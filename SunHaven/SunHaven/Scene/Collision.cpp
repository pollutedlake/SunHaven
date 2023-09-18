#include "Stdafx.h"
#include "MineScene.h"
#include "DizzyScene.h"
#include "DynusScene.h"

void MineScene::collision(void)
{
	RECT rcTemp1, rcTemp2;

	for (int i = 0; i < _em->getEnemys().size(); i++)
	{
		if (IntersectRect(&rcTemp1, &_player->getPlayerRC(), &_em->getEnemys()[i]->getRcAttack()))
		{
			_player->hitDamage(2.0f);
		}
	}

	for (int i = 0; i < _em->getEnemys().size(); i++)
	{
		if(_player->isSlash())
		{
			if (IntersectRect(&rcTemp1, &_player->getSwingRC(), &CAMERA->worldToCameraRect(_em->getEnemys()[i]->getRect())))
			{
				_em->getEnemys()[i]->hitDamage(_player->getAttackDamage() / 2);
			}
		}
	}

	for (int i = 0; i < _em->getEnemys().size(); i++)
	{
		for (int j = 0; j < _om->getObjectList().size(); j++)
		{
			if (IntersectRect(&rcTemp1, &_om->getObjectList()[j]->getRC(), &_em->getEnemys()[i]->getRect()))
			{
				_em->getEnemys()[i]->setX(_em->getEnemys()[i]->getX() - 0.1f);
				_em->getEnemys()[i]->setY(_em->getEnemys()[i]->getY() - 0.1f);
			}
		}
	}
}

void DizzyScene::collision(void)
{
	RECT rcTemp1;

	if (IntersectRect(&rcTemp1, &_player->getPlayerRC(), &_dizzy->getRcSpinAttack()))
	{
		_player->hitDamage(5.0f);
	}
	if (_player->isSlash())
	{
		if (IntersectRect(&rcTemp1, &_player->getSwingRC(), &CAMERA->worldToCameraRect(_dizzy->getRcDizzy())))
		{
			_dizzy->hitDamage(_player->getAttackDamage());
		}
	}
}

void DynusScene::collision(void)
{
	RECT rcTemp1, rcTemp3, rcTemp4;

	for (int i = 0; i < _em->getEnemys().size(); i++)
	{
		if (IntersectRect(&rcTemp1, &_player->getPlayerRC(), &_em->getEnemys()[i]->getRcAttack()))
		{
			_player->hitDamage(4.0f);
		}
	}
	if (_player->isSlash())
	{
		if (IntersectRect(&rcTemp1, &_player->getSwingRC(), &CAMERA->worldToCameraRect(_dynus->getRcDynus())))
		{
			_dynus->hitDamage(_player->getAttackDamage());
		}
	}
	for (int i = 0; i < _em->getEnemys().size(); i++)
	{
		if (_player->isSlash())
		{
			if (IntersectRect(&rcTemp1, &_player->getSwingRC(), &CAMERA->worldToCameraRect(_em->getEnemys()[i]->getRect())))
			{
				_em->getEnemys()[i]->hitDamage(_player->getAttackDamage() / 2);
				if (_em->getEnemys()[i]->getHP() == 0)
				{
					_em->removeEnemy(i);
				}
			}
		}
	}

	if (IntersectRect(&rcTemp3, &_player->getSwingRC(), &_dynus->getRcGuardMine1()))
	{
 		_dynus->setIsGM1Remove(true);
	}

	if (IntersectRect(&rcTemp4, &_player->getSwingRC(), &_dynus->getRcGuardMine2()))
	{
		_dynus->setIsGM2Remove(true);
	}
}