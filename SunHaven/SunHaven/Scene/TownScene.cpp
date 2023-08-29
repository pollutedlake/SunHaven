#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
    _frameTick = 0.0f;
    return S_OK;
}

void TownScene::update(void)
{
    if (0.2f + _frameTick <= TIMEMANAGER->getWorldTime())
    {
        _frameTick = TIMEMANAGER->getWorldTime();
        IMAGEMANAGER->findGPImage("FrameDropTest")->setFrameX((IMAGEMANAGER->findGPImage("FrameDropTest")->getFrameX() + 1));
    }
}

void TownScene::render(void)
{
    IMAGEMANAGER->GPFrameRender("FrameDropTest", getMemDC(),
        CENTER_X, CENTER_Y, 1, 1,
        IMAGEMANAGER->findGPImage("FrameDropTest")->getFrameX(), IMAGEMANAGER->findGPImage("FrameDropTest")->getFrameY(),
        InterpolationModeNearestNeighbor, 0);
}

void TownScene::release(void)
{
}
