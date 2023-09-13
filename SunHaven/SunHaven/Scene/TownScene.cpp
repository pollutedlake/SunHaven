#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
    _test = IMAGEMANAGER->findGPImage("Tree1Cut");
    _angle = 0.0f;
    return S_OK;
}

void TownScene::update(void)
{
    _angle += 0.1f;
}

void TownScene::render(void)
{
    _test->GPRender(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, 1.0f, 1.0f, 0, 0, _test->getWidth(), _test->getHeight(), InterpolationModeNearestNeighbor, _angle);
}

void TownScene::release(void)
{
}

void TownScene::skillPopUp(void)
{

}
