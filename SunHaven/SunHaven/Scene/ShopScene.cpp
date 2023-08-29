// ±è¼ºÀÇ
#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void)
{
	_temp = new Inventory;
	_temp->init();

	return S_OK;
}

void ShopScene::release(void)
{
}

void ShopScene::update(void)
{
}

void ShopScene::render(void)
{
	_temp->render();
}
