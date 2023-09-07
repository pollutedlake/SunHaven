#include "Stdafx.h"
#include "Tree.h"

HRESULT Tree::init(void)
{
	
	return S_OK;
}

HRESULT Tree::init(LivingObjectType type, POINT tilePos)
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
	case TREE1:
		_offsetX = -3;
		_offsetY = -48;
		break;
	case TREE2:
		_offsetX = 3;
		_offsetY = -42;
		break;
	}
	return S_OK;
}

void Tree::update(void)
{
}

void Tree::render(void)
{
	if(_halfTrans)
	{
		_image->alphaRender(getMemDC(), _rc.left, _rc.top, (_rc.right - _rc.left), (_rc.bottom - _rc.top), 0, 0, _image->getWidth(), _image->getHeight(), 128);
	}
	else
	{
		_image->render(getMemDC(), _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top, 0, 0, _image->getWidth(), _image->getHeight());
	}
}

void Tree::release(void)
{
}
