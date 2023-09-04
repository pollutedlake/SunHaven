// ¹Î¿ë½Ä
#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("³óÀå", "FarmMap.bmp", 2400, 2400);
	IMAGEMANAGER->addImage("Ãæµ¹", "FarmMapCollision.bmp", 2400, 2400);

	_player = new Player;
	_player->init(1480, 850);
	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(2184 - WINSIZE_X / 2);
	_camera->setLimitBottom(2400 - WINSIZE_Y / 2);

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
	//_player->setPlayerRect(_camera->worldToCamera(_player->getPlayerPosition()));
}

void FarmScene::render(void)
{
	_bg->render(getMemDC(), _camera->worldToCameraX(0), _camera->worldToCameraY(0));
	_player->render();
}
