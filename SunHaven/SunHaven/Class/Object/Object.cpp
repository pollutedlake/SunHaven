#include "Stdafx.h"
#include "Object.h"

HRESULT Object::init(void)
{
	return  S_OK;
}

HRESULT Object::init(LivingObjectType type, POINT tilePos)
{
	_type = type;
	char str[64];
	wsprintf(str, "Object%d", (int)type + 1);
	_image = IMAGEMANAGER->findImage(str);
	_tilePos = tilePos;
	_rc = RectMake(tilePos.x * TILEWIDTH * 2, tilePos.y * TILEHEIGHT * 2, TILEWIDTH * 2, TILEHEIGHT * 2);
	switch (_type)
	{
	case GRASS1:
		_offsetY = -12;
		break;
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

void Object::release(void)
{

}

void Object::update(void)
{
	
}

void Object::render(void)
{
	_image->render(getMemDC(), _cx + _offsetX * 2 - _image->getWidth(), _cy + _offsetY * 2 - _image->getHeight(), _image->getWidth() * 2, _image->getHeight() * 2,
		0, 0, _image->getWidth(), _image->getHeight());
}

void Object::render(HDC hdc)
{
	_image->render(hdc, _tilePos.x * TILEWIDTH + TILEWIDTH / 2 - _image->getWidth() / 2 + _offsetX,
		_tilePos.y * TILEHEIGHT + TILEHEIGHT / 2 - _image->getHeight() / 2 + _offsetY);
}

void Object::updateCameraPos(float cx, float cy)
{
	_cx = cx;
	_cy = cy;
}

void Object::renderToPoint(POINT point)
{
	_image->alphaRender(getMemDC(), point.x - _image->getWidth() / 2 + _offsetX, point.y - _image->getHeight() / 2 + _offsetY, 128);
}
