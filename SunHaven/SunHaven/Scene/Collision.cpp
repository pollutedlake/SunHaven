#include "Stdafx.h"
#include "DynusScene.h"

void DynusScene::collision(void)
{
	RECT rcTemp1, rcTemp2;

	if (IntersectRect(&rcTemp1, &_player->getSwordSwingRC(), &_dynus->getRcGuardMine1()))
	{
		_dynus->setIsGM1Remove(true);
	}

	if (IntersectRect(&rcTemp2, &_player->getSwordSwingRC(), &_dynus->getRcGuardMine2()))
	{
		_dynus->setIsGM2Remove(true);
	}
}