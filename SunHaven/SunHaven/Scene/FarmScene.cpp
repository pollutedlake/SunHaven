// �ο��
#include "Stdafx.h"
#include "FarmScene.h"
#include "../Class/UI.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("����", "FarmMap.bmp", 4800, 4800);
	IMAGEMANAGER->addImage("�浹", "FarmMapCollision.bmp", 4800, 4800);

	
	_player = new Player;
	_player->init(2800, 1400);


	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(4368 - WINSIZE_X / 2);
	_camera->setLimitBottom(4800 - WINSIZE_Y / 2);

	_om = new ObjectManager;
	_om->init();
	_om->setCameraAddress(_camera);



	_player->setPlayerPosition(PointMake(2496, 1500));


	_ui = new UI;
	_ui->init("Farm");

	return S_OK;
}

void FarmScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_om->release();
	SAFE_DELETE(_om);
}

void FarmScene::update(void)
{
	_player->update();
	_camera->setPosition(_player->getPlayerPosition());
	//_player->setPlayerPosition(_camera->worldToCamera(_player->getPlayerPosition()));

	_player->worldToCamera(_camera->worldToCamera
	(_player->getPlayerPosition()));
	_om->update();

	Collision();
}

void FarmScene::render(void)
{
	_bg->render(getMemDC(), _camera->worldToCameraX(0),
		_camera->worldToCameraY(0));



	_player->render();
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getPlayerRC(), &_om->getObjectList()[i]->getTransParentRC()))
		{
			_om->getObjectList()[i]->halfTransRender();
		}
		else
		{
			_om->getObjectList()[i]->render();
		}
	}

	if (KEYMANAGER->isToggleKey('W'))
	{
		IMAGEMANAGER->render("�浹", getMemDC(), _camera->worldToCameraX(0),
			_camera->worldToCameraY(0));
	}

	
	_ui->render();
}

void FarmScene::Collision(void)
{
	for (int i = 0; i < _om->getObjectList().size(); i++)
	{
		RECT temp;

		if (IntersectRect(&temp,
			&RectMakeCenter(_player->getPlayerPosition().x,
				_player->getPlayerPosition().y,48,52),
			&_om->getObjectList()[i]->getCollisionRC()))
		{
			
		}
	}
}