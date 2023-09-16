#include "Stdafx.h"
#include "MineScene.h"
#include "DizzyScene.h"
#include "DynusScene.h"

void MineScene::collision(void)
{
	RECT rcTemp1;

	for (int i = 0; i < _em->getEnemys().size(); i++)
	{
		if (IntersectRect(&rcTemp1, &_player->getPlayerRC(), &_em->getEnemys()[i]->getRcAttack()))
		{
			_player->hitDamage(2.0f);
		}
	}
}

void DizzyScene::collision(void)
{
	RECT rcTemp1;

	if (IntersectRect(&rcTemp1, &_player->getPlayerRC(), &_dizzy->getRcSpinAttack()))
	{
		cout << "충돌 " << endl;
		_player->hitDamage(5.0f);
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

	if (IntersectRect(&rcTemp3, &_player->getSwingRC(), &_dynus->getRcGuardMine1()))
	{
		cout << "충돌 " << endl;
 		_dynus->setIsGM1Remove(true);
	}

	if (IntersectRect(&rcTemp4, &_player->getSwingRC(), &_dynus->getRcGuardMine2()))
	{
		cout << "충돌 " << endl;

		_dynus->setIsGM2Remove(true);
	}
}