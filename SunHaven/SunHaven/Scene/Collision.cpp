#include "Stdafx.h"
#include "DynusScene.h"

void DynusScene::collision(void)
{
	RECT rcTemp1, rcTemp2;

	if (IntersectRect(&rcTemp1, &_player->getSwordSlashRC(), &_dynus->getRcGuardMine1()))
	{
		cout << "충돌 " << endl;
 		_dynus->setIsGM1Remove(true);
	}

	if (IntersectRect(&rcTemp2, &_player->getSwordSlashRC(), &_dynus->getRcGuardMine2()))
	{
		cout << "충돌 " << endl;

		_dynus->setIsGM2Remove(true);
	}
}