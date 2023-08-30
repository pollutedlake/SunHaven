#include "Stdafx.h"
#include "UI.h"

HRESULT Button::init(void)
{
	return S_OK;
}

HRESULT Button::init(float x, float y, int width, int height, char* imageName, void(*onClick)())
{
	return S_OK;
}

void Button::release(void)
{
}

void Button::update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		_onCusor = true;
		_image->setFrameX(1);
	}
	else
	{
		_onCusor = false;
		_image->setFrameX(0);
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _onCusor)
	{
		_click = true;
		_image->setFrameX(2);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _click)
	{
		_image->setFrameX(2);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _click)
	{
		_click = false;
		_image->setFrameX(1);
		if(_onCusor)
		{
			/*if(_onClick != nullptr)
			{
				_onClick();
			}*/
		}
	}
}

void Button::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _width, _height, _image->getFrameX(), 0);
}

Button::Button() : _x(0.0f), _y(0.0f), _width(0), _height(0), _click(false), _onCusor(false)
{
}

//void UI::addButton(float x, float y, int width, int height, char* imageName, void(*onClick)(int* num))
//{
//	Button button;
//	button._x = x;
//	button._y = y;
//	button._image = IMAGEMANAGER->findImage(imageName);
//	button._onClick2 = onClick;
//	button._click = false;
//	button._onCusor = false;
//	button.width = width;
//	button.height = height;
//	button._rc = RectMakeCenter(button._x, button._y, button.width, button.height);
//	_vButton.push_back(button);
//}
