#include "Stdafx.h"
#include "Grass.h"

HRESULT Grass::init(void)
{
	switch (_type)
	{
	case GRASS1:
		_maxHp = 5;
		break;
	case GRASS2:
		_maxHp = 10;
		break;
	}
	_curHp = _maxHp;
	return S_OK;
}

HRESULT Grass::init(LivingObjectType type, POINT tilePos)
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
	case GRASS1:
		_offsetY = -12;
		break;
	}
	return S_OK;
}

void Grass::release(void)
{
}

void Grass::update(void)
{
}

void Grass::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top, 0, 0, _image->getWidth(), _image->getHeight());
}
