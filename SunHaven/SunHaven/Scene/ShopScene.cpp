// ±è¼ºÀÇ
#include "Stdafx.h"
#include "ShopScene.h"


HRESULT ShopScene::init(void)
{
	IMAGEMANAGER->addImage("Ãæµ¹", "FarmMapCollision.bmp", 3600, 3600);
	_player = new Player;
	_player->init(700,500);
	
	
	
	
	return S_OK;
}

void ShopScene::release(void)
{
	_player->release();
    SAFE_DELETE(_player);
	
}

void ShopScene::update(void)
{
	_player->update();
	
	
}

void ShopScene::render(void)
{
	IMAGEMANAGER->render("Shop_Bg", getMemDC());
	_player->render();
	
	
	IMAGEMANAGER->render("Cursor", getMemDC(), _ptMouse.x, _ptMouse.y);
}

