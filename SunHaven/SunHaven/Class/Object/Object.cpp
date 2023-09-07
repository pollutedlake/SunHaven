#include "Stdafx.h"
#include "Object.h"

HRESULT Object::init(void)
{
	return  S_OK;
}

HRESULT Object::init(LivingObjectType type, POINT tilePos)
{
	
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
	_rc = RectMake(_cx + _offsetX * 1.5 - _image->getWidth(), _cy + _offsetY * 1.5 - _image->getHeight(), _image->getWidth() * 1.5, _image->getHeight() * 1.5);
}

void Object::renderToPoint(POINT point)
{
	_image->alphaRender(getMemDC(), point.x - _image->getWidth() / 2 + _offsetX, point.y - _image->getHeight() / 2 + _offsetY, 128);
}

void Object::renderHpBar()
{
	if (_curHp < _maxHp)
	{
		_hpBar->render();
	}
}
