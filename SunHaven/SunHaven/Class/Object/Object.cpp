#include "Stdafx.h"
#include "Object.h"

HRESULT Object::init(void)
{
	return  S_OK;
}

HRESULT Object::init(Type::ObjectType type, POINT tilePos)
{
	_type = type;
	char str[64];
	wsprintf(str, "Object%d", (int)type);
	_image = IMAGEMANAGER->findImage(str);
	_tilePos = tilePos;
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
	_image->render(getMemDC(), _rc.left, _rc.top);
}