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


	_camera = new Camera;
	_camera->init();
	_camera->setPosition(_player->getPlayerPosition());
	_camera->setLimitRight(1280 - WINSIZE_X / 2);
	_camera->setLimitBottom(720 - WINSIZE_Y / 2);

	wsprintf(_text, "DizzyScene");

	return S_OK;
}

void DizzyScene::release(void)
{
	_dizzy->release();
	SAFE_DELETE(_dizzy);

	_player->release();
	SAFE_DELETE(_player);

	_camera->release();
	SAFE_DELETE(_camera);
}

void DizzyScene::update(void)
{
	_dizzy->update();

	_player->update();
	_player->worldToCamera(_camera->worldToCamera(_player->getPlayerPosition()));

	_camera->setPosition(_player->getPlayerPosition());
	_camera->update();

}

void DizzyScene::render(void)
{
	IMAGEMANAGER->render("DizzyLayer", getMemDC(), 0, 0, _camera->getPosition().x - WINSIZE_X / 2,
		_camera->getPosition().y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y);

	_dizzy->render();
	_player->render();
}

void DizzyScene::collision(void)
{
}
