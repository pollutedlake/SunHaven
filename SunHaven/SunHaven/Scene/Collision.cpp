#include "Stdafx.h"
#include "DynusScene.h"

void DynusScene::collision(void)
{
	/*for (int i = 0; i < _em->getEnemys().size(); i++)
	{
		if (getDistance(_em->getEnemys()[i]->getX(), _em->getEnemys()[i]->getY(),
			_player->getPosition().x, _player->getPosition().y) > 50 &&
			getDistance(_em->getEnemys()[i]->getX(), _em->getEnemys()[i]->getY(),
				_player->getPosition().x, _player->getPosition().y) < 200)
		{
			cout << "적이 쫓아간다" << endl;

			_em->getEnemys()[i]->setX(_em->getEnemys()[i]->getX() +
				cosf(getAngle((_em->getEnemys()[i]->getRect().left + _em->getEnemys()[i]->getRect().right) / 2,
					(_em->getEnemys()[i]->getRect().bottom + _em->getEnemys()[i]->getRect().top) / 2,
					_player->getPosition().x,
					_player->getPosition().y)) * 2.0f);

			_em->getEnemys()[i]->setY(_em->getEnemys()[i]->getY() -
				sinf(getAngle((_em->getEnemys()[i]->getRect().left + _em->getEnemys()[i]->getRect().right) / 2,
					(_em->getEnemys()[i]->getRect().bottom + _em->getEnemys()[i]->getRect().top) / 2,
					_player->getPosition().x,
					_player->getPosition().y)) * 2.0f);
		}

		else if (getDistance(_em->getEnemys()[i]->getX(), _em->getEnemys()[i]->getY(),
			_player->getPosition().x, _player->getPosition().y) <= 50)
		{
			cout << "적이 공격한다" << endl;

			_em->getEnemys()[i]->attack();
		}
	}*/
}