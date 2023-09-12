#include "Stdafx.h"
#include "DizzyScene.h"

HRESULT DizzyScene::init(void)
{
	_dizzy = new Dizzy;
	_player = new Player;

	_player->init(CENTER_X, CENTER_Y + 200);
	_dizzy->init();

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
