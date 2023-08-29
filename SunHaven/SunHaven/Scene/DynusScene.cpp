// Á¤¼ºÁø
#include "Stdafx.h"
#include "DynusScene.h"

HRESULT DynusScene::init(void)
{
	_dynus = new Dynus;
	_dynus->init();

	_em = new EnemyManager;
	//_em->init();

	_x = _y = 0.0f;

	wsprintf(_text, "DynusScene");

	return S_OK;
}

void DynusScene::release(void)
{
	_dynus->release();
	//_em->release();
}

void DynusScene::update(void)
{
	_dynus->update();
	//_em->update();
}

void DynusScene::render(void)
{
	IMAGEMANAGER->render("DynusLayer0", getMemDC(), 0, 0);
	_dynus->render();
	//_em->render();
}
