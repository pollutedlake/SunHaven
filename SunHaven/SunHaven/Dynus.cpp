#include "stdafx.h"
#include "Dynus.h"

HRESULT Dynus::init(void)
{
	return S_OK;
}

HRESULT Dynus::init(const char* imageName, POINT position)
{
	_x = position.x;
	_y = position.y;

	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	_dynusImg = IMAGEMANAGER->findImage(imageName);
	_rcDynus = RectMakeCenter(_x, _y,
		_dynusImg->getFrameWidth(), _dynusImg->getFrameHeight());

	/*_dynusImg = IMAGEMANAGER->addImage("다이너스", "Resource/Images/Dynus/Dynus_Spell.bmp",
		3804, 3564, true, RGB(255, 0, 255));
	_dynusAni = new Animation;
	_dynusAni->init(_dynusImg->getWidth(), _dynusImg->getHeight(), 634, 297);
	_dynusAni->setDefPlayFrame(false, true);
	_dynusAni->setFPS(12);*/

	return S_OK;
}

void Dynus::release(void)
{
}

void Dynus::update(void)
{
}

void Dynus::render(void)
{
}

void Dynus::move(void)
{
}

void Dynus::draw(void)
{
}
