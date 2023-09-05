// ¹Î¿ë½Ä
#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("³óÀå", "FarmMap.bmp", 4800, 4800);
	IMAGEMANAGER->addImage("Ãæµ¹", "FarmMapCollision.bmp", 4800, 4800);

	
	_player = new Player;
	_player->init(1600,1600);


	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(4368 - WINSIZE_X / 2);
	_camera->setLimitBottom(4800 - WINSIZE_Y / 2);

	_om = new ObjectManager;
	_om->init();
	_om->setCameraAddress(_camera);


	_player->setPlayerPosition(PointMake(1600, 2800));




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
}

void FarmScene::render(void)
{
	_bg->render(getMemDC(), _camera->worldToCameraX(0),
		_camera->worldToCameraY(0));

	_om->render();

	if (KEYMANAGER->isToggleKey('W'))
	{
		IMAGEMANAGER->render("Ãæµ¹", getMemDC(), _camera->worldToCameraX(0),
			_camera->worldToCameraY(0));
	}

	_player->render();
}
