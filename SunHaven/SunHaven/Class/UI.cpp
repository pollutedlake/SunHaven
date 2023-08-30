#include "Stdafx.h"
#include "UI.h"

HRESULT NormalButton::init(void)
{
	return S_OK;
}

HRESULT NormalButton::init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, char* str, COLORREF color, int fontSize, int offsetY)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_image = IMAGEMANAGER->findImage(imageName);
	_onClick = move(onClick);
	_click = false;
	_frameX = 0;
	_frameY = 0;
	_onCusor = false;
	_rc = RectMakeCenter(_x, _y, _width, _height);
	strcpy_s(_str, 64, str);
	_color = color;
	_fontSize = fontSize;
	_offsetY = offsetY;
	return S_OK;
}

void NormalButton::release(void)
{
}

void NormalButton::update(void)
{
	if (PtInRect(&_rc, _ptMouse) && !_click)
	{
		_onCusor = true;
		_frameX = 1;
	}
	else if(!_click)
	{
		_onCusor = false;
		_frameX = 0;
	}
}

void NormalButton::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _width, _height, _frameX, _frameY);
	if(_fontSize != NULL)
	{
		SetTextAlign(getMemDC(), TA_CENTER);
		FONTMANAGER->textOut(getMemDC(), _x, _y + _offsetY, "배달의민족 을지로체", _fontSize, 100, _str, strlen(_str), _color);
		SetTextAlign(getMemDC(), TA_LEFT);
	}
}

void NormalButton::buttonDown()
{
	if (_onCusor)
	{
		_click = true;
		_frameX = 2;
	}
}

void NormalButton::buttonUp(int num)
{
	if (_click)
	{
		_click = false;
		_frameX = 0;
		if (_onCusor)
		{
			if (_onClick != nullptr)
			{
				_onClick(num);
			}
		}
	}
}

NormalButton::NormalButton()
{

}

HRESULT ToggleButton::init(void)
{
	return S_OK;
}

HRESULT ToggleButton::init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, bool toggle)//char* str, COLORREF color, int fontSize, int offsetY)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_image = IMAGEMANAGER->findImage(imageName);
	_onClick = move(onClick);
	_click = false;
	if(toggle)
	{
		_frameX = 0;
	}
	else
	{
		_frameX = 1;
	}
	_frameY = 0;
	_onCusor = false;
	_rc = RectMakeCenter(_x, _y, _width, _height);
	return S_OK;
}

void ToggleButton::release(void)
{
	
}

void ToggleButton::update(void)
{
	if (PtInRect(&_rc, _ptMouse) && !_click)
	{
		_onCusor = true;
	}
	else if (!_click)
	{
		_onCusor = false;
	}
}

void ToggleButton::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _width, _height, _frameX, _frameY);
}

void ToggleButton::buttonDown()
{
	if (_onCusor)
	{
		_click = true;
	}
}

void ToggleButton::buttonUp(int num)
{
	if (_click)
	{
		_click = false;
		_frameX++;
		if (_frameX > _image->getMaxFrameX())
		{
			_frameX = 0;
		}
		if (_onCusor)
		{
			if (_onClick != nullptr)
			{
				_onClick(num);
			}
		}
	}
}

ToggleButton::ToggleButton()
{
}

HRESULT Button::init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, char* str, COLORREF color, int fontSize, int offsetY)
{
	return E_NOTIMPL;
}

HRESULT Button::init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, bool toggle)
{
	return E_NOTIMPL;
}

void Button::buttonDown()
{
}

void Button::buttonUp(int num)
{
}
