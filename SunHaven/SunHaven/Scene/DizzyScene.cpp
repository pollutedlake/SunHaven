#include "Stdafx.h"
#include "DizzyScene.h"

HRESULT DizzyScene::init(void)
{
	IMAGEMANAGER->addImage("DizzyMapCollision", "DizzyMapCollision.bmp", 1464 * 1.5, 1008 * 1.5);

	_player = new Player;
	_player->init(CENTER_X, CENTER_Y + 200, "DizzyMapCollision");

	_dizzy = new Dizzy;
	_dizzy->setPlayerMemoryAddress(_player);
	_dizzy->init();

	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->setLimitRight(2196 - WINSIZE_X / 2);
	CAMERA->setLimitBottom(1512 - WINSIZE_Y / 2);

	wsprintf(_text, "DizzyScene");

	return S_OK;
}

void DizzyScene::release(void)
{
	_dizzy->release();
	SAFE_DELETE(_dizzy);

	_player->release();
	SAFE_DELETE(_player);
}

void DizzyScene::update(void)
{
	_dizzy->update();

	_player->update();
	_player->worldToCamera(CAMERA->worldToCamera(_player->getPlayerPosition()));

	CAMERA->setPosition(_player->getPlayerPosition());
	CAMERA->update();
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Dynus");
	}
}

void DizzyScene::render(void)
{
	IMAGEMANAGER->render("DizzyLayer", getMemDC(), 0, 0, CAMERA->getPosition().x - WINSIZE_X / 2,
		CAMERA->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y);

	_dizzy->render();
	_player->render();
}

void DizzyScene::collision(void)
{
}
