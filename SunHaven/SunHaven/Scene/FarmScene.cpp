// �ο��
#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("����", "FarmMap.bmp", 4800, 4800);
	IMAGEMANAGER->addImage("�浹", "FarmMapCollision.bmp", 4800, 4800);

	
	_player = new Player;
	_player->init(1600,1600);

	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(4368 - WINSIZE_X / 2);
	_camera->setLimitBottom(4800 - WINSIZE_Y / 2);




	_player->setPlayerPosition(PointMake(3200, 1600));




	return S_OK;
}

void FarmScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
}

void FarmScene::update(void)
{
	_player->update();
	_camera->setPosition(_player->getPlayerPosition());
	//_player->setPlayerPosition(_camera->worldToCamera(_player->getPlayerPosition()));
	_player->worldToCamera(_camera->worldToCamera
	(_player->getPlayerPosition()));
}

void FarmScene::render(void)
{
	_bg->render(getMemDC(), _camera->worldToCameraX(0),
		_camera->worldToCameraY(0));


	if (KEYMANAGER->isToggleKey('W'))
	{
		IMAGEMANAGER->render("�浹", getMemDC(), _camera->worldToCameraX(0),
			_camera->worldToCameraY(0));
	}

	_player->render();
}
