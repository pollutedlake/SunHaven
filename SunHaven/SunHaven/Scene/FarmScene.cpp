// ¹Î¿ë½Ä
#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	_player = new Player;
	_player->init(1.5,2.5);
	return S_OK;
}

void FarmScene::release(void)
{
	_player->release();
}

void FarmScene::update(void)
{
	_player->update();
}

void FarmScene::render(void)
{
	_player->render();
}
