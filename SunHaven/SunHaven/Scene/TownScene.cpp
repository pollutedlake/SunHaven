#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
	IMAGEMANAGER->addImage("435435",
		"Resources/Images/Player/fishing_greatzone.bmp",
		10, 20, true, RGB(255, 0, 255));

    return S_OK;
}

void TownScene::update(void)
{

}

void TownScene::render(void)
{
	IMAGEMANAGER->render("435435", getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, RND->getInt(50), 50, 0, 0, 10, 20);
}

void TownScene::release(void)
{
}
