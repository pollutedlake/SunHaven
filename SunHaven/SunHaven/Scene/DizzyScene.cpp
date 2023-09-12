#include "Stdafx.h"
#include "DizzyScene.h"

HRESULT DizzyScene::init(void)
{
	IMAGEMANAGER->addImage("Ãæµ¹", "FarmMapCollision.bmp", 3600, 3600);

	_dizzy = new Dizzy;
	_player = new Player;

	_player->init(CENTER_X, CENTER_Y + 200, "/*Ãæµ¹¸Ê*/");
	_dizzy->init();


	_dizzy->setPlayerMemoryAddress(_player);

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
}

void DizzyScene::render(void)
{
	IMAGEMANAGER->render("DizzyLayer", getMemDC(), 0, 0, 900, 700, WINSIZE_X, WINSIZE_Y);
	_dizzy->render();
	_player->render();
}

void DizzyScene::collision(void)
{
}
