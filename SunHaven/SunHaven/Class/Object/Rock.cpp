#include "Stdafx.h"
#include "Rock.h"

HRESULT Rock::init(void)
{
	return S_OK;
}

HRESULT Rock::init(LivingObjectType type, POINT tilePos)
{
	_type = type;
	char str[64];
	wsprintf(str, "Object%d", (int)type + 1);
	_image = IMAGEMANAGER->findImage(str);
	_tilePos = tilePos;
	_collisionRC = RectMake(tilePos.x * TILEWIDTH * 2, tilePos.y * TILEHEIGHT * 2, TILEWIDTH * 2, TILEHEIGHT * 2);
	_halfTrans = false;
	switch (_type)
	{
	case ROCK1:
		_maxHp = 5;
		break;
	case ROCK2:
		_maxHp = 10;
		break;
	}
	_curHp = _maxHp * RND->getFloat(1.0f);
	_hpBar = new ProgressBar;
	_hpBar->init("ObjectHpBar", "", "ObjectHpBarFill", NULL, NULL, 36, 7);
	return S_OK;
}

void Rock::release(void)
{
}

void Rock::update(void)
{
	_hpBar->setX(_cx - 25);
	_hpBar->setY(_cy - 50);
	_hpBar->setGauge(_curHp, _maxHp);
	_hpBar->update();
}

void Rock::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top, 0, 0, _image->getWidth(), _image->getHeight());
}
