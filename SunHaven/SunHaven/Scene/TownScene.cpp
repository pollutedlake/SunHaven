#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
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
