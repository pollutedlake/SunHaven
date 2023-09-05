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
	switch (_type)
	{
	case TREE1:
		_offsetY = -48;
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
	_image->render(getMemDC(), _tilePos.x * TILEWIDTH + TILEWIDTH / 2 - _image->getWidth() / 2 + _offsetX, 
		_tilePos.y * TILEHEIGHT + TILEHEIGHT / 2 - _image->getHeight() / 2 + _offsetY);
}

void Object::render(HDC hdc)
{
	_image->render(hdc, _tilePos.x * TILEWIDTH + TILEWIDTH / 2 - _image->getWidth() / 2 + _offsetX,
		_tilePos.y * TILEHEIGHT + TILEHEIGHT / 2 - _image->getHeight() / 2 + _offsetY);
}

void Object::renderToMouse()
{
	_image->alphaRender(getMemDC(), _ptMouse.x - _image->getWidth() / 2 + _offsetX, _ptMouse.y - _image->getHeight() / 2 + _offsetY, 128);
}
