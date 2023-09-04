// �ο��
#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("����", "FarmMap.bmp", 2400, 2400);
	IMAGEMANAGER->addImage("�浹", "FarmMapCollision.bmp", 2400, 2400);

	_player = new Player;
	_player->init(1.5,2.5);

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
}

void FarmScene::render(void)
{
	_bg->render(getMemDC());
	_player->render();
}
