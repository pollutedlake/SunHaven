#include "Stdafx.h"
#include "UI.h"

HRESULT NormalButton::init(void)
{
	return S_OK;
}

HRESULT NormalButton::init(float x, float y, int width, int height, char* imageName, function<void(int)> onClick, char* str, COLORREF color, int fontSize, int offsetY)
{
	_button._x = x;
	_button._y = y;
	_button._width = width;
	_button._height = height;
	_button._image = IMAGEMANAGER->findImage(imageName);
	_button._onClick = move(onClick);
	_button._click = false;
	_button._frameX = 0;
	_button._frameY = 0;
	_button._onCusor = false;
	_button._rc = RectMakeCenter(_button._x, _button._y, _button._width, _button._height);
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
	if (PtInRect(&_button._rc, _ptMouse) && !_button._click)
	{
		_button._onCusor = true;
		_button._frameX = 1;
	}
	else if(!_button._click)
	{
		_button._onCusor = false;
		_button._frameX = 0;
	}
}

void NormalButton::render(void)
{
	_button._image->frameRender(getMemDC(), _button._rc.left, _button._rc.top, _button._width, _button._height, _button._frameX, _button._frameY);
	if(_fontSize != NULL)
	{
		SetTextAlign(getMemDC(), TA_CENTER);
		FONTMANAGER->textOut(getMemDC(), _button._x, _button._y + _offsetY, "배달의민족 을지로체", _fontSize, 100, _str, strlen(_str), _color);
		SetTextAlign(getMemDC(), TA_LEFT);
	}
}

void NormalButton::buttonDown()
{
	if (_button._onCusor)
	{
		_button._click = true;
		_button._frameX = 2;
	}
}

void NormalButton::buttonUp(int num)
{
	if (_button._click)
	{
		_button._click = false;
		_button._frameX = 0;
		if (_button._onCusor)
		{
			if (_button._onClick != nullptr)
			{
				_button._onClick(num);
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
	_button._x = x;
	_button._y = y;
	_button._width = width;
	_button._height = height;
	_button._image = IMAGEMANAGER->findImage(imageName);
	_button._onClick = move(onClick);
	_button._click = false;
	if(toggle)
	{
		_button._frameX = 0;
	}
	else
	{
		_button._frameX = 1;
	}
	_button._frameY = 0;
	_button._onCusor = false;
	_button._rc = RectMakeCenter(_button._x, _button._y, _button._width, _button._height);
	return S_OK;
}

void ToggleButton::release(void)
{
	
}

void ToggleButton::update(void)
{
	if (PtInRect(&_button._rc, _ptMouse) && !_button._click)
	{
		_button._onCusor = true;
	}
	else if (!_button._click)
	{
		_button._onCusor = false;
	}
}

void ToggleButton::render(void)
{
	_button._image->frameRender(getMemDC(), _button._rc.left, _button._rc.top, _button._width, _button._height, _button._frameX, _button._frameY);
}

void ToggleButton::buttonDown()
{
	if (_button._onCusor)
	{
		_button._click = true;
	}
}

void ToggleButton::buttonUp(int num)
{
	if (_button._click)
	{
		_button._click = false;
		_button._frameX++;
		if (_button._frameX > _button._image->getMaxFrameX())
		{
			_button._frameX = 0;
		}
		if (_button._onCusor)
		{
			if (_button._onClick != nullptr)
			{
				_button._onClick(num);
			}
		}
	}
}

ToggleButton::ToggleButton()
{
}

HRESULT RadioButton::init(void)
{
	return S_OK;
}

HRESULT RadioButton::init(int buttonN, float x[], float y[], int width[], int height[], char* imageName, function<void(int)> onClick[], char* str[], COLORREF color, int fontSize, int offsetY)
{
	for (int i = 0; i < buttonN; i++)
	{
		Button* button = new Button;
		button->_x = x[i];
		button->_y = y[i];
		button->_width = width[i];
		button->_height = height[i];
		button->_image = IMAGEMANAGER->findImage(imageName);
		button->_onClick = onClick[i];
		button->_click = false;
		button->_frameX = 0;
		button->_frameY = 0;
		button->_onCusor = false;
		button->_rc = RectMakeCenter(button->_x, button->_y, button->_width, button->_height);
		_str.push_back(str[i]);
		_vButtons.push_back(button);
	}
	_color = color;
	_fontSize = fontSize;
	_offsetY = offsetY;
	return S_OK;
}

void RadioButton::release(void)
{
	for (_viButtons = _vButtons.begin(); _viButtons != _vButtons.end();)
	{
		SAFE_DELETE(*_viButtons);
		_viButtons = _vButtons.erase(_viButtons);
	}
}

void RadioButton::update(void)
{
	for (_viButtons = _vButtons.begin(); _viButtons != _vButtons.end(); ++_viButtons)
	{
		if (PtInRect(&(*_viButtons)->_rc, _ptMouse))
		{
			(*_viButtons)->_onCusor = true;
			if(!(*_viButtons)->_click)
			{
				(*_viButtons)->_frameX = 1;
			}
		}
		else
		{
			(*_viButtons)->_onCusor = false;
			if (!(*_viButtons)->_click)
			{
				(*_viButtons)->_frameX = 0;
			}
		}
	}
}

void RadioButton::render(void)
{
	for (_viButtons = _vButtons.begin(); _viButtons != _vButtons.end(); ++_viButtons)
	{
		(*_viButtons)->_image->frameRender(getMemDC(), (*_viButtons)->_rc.left, (*_viButtons)->_rc.top, (*_viButtons)->_width, (*_viButtons)->_height, (*_viButtons)->_frameX, (*_viButtons)->_frameY);
		if (_fontSize != NULL)
		{
			SetTextAlign(getMemDC(), TA_CENTER);
			FONTMANAGER->textOut(getMemDC(), (*_viButtons)->_x, (*_viButtons)->_y + _offsetY, "배달의민족 을지로체", _fontSize, 100, 
				_str[_viButtons - _vButtons.begin()], strlen(_str[_viButtons - _vButtons.begin()]), _color);
			SetTextAlign(getMemDC(), TA_LEFT);
		}
	}
}

void RadioButton::buttonDown()
{
	for (_viButtons = _vButtons.begin(); _viButtons != _vButtons.end(); ++_viButtons)
	{
		if ((*_viButtons)->_onCusor)
		{
			(*_viButtons)->_frameX = 2;
			(*_viButtons)->_click = true;
			for (auto _viButtons2 = _vButtons.begin(); _viButtons2 != _vButtons.end(); ++_viButtons2)
			{
				if (_viButtons == _viButtons2)
				{
					continue;
				}
				(*_viButtons2)->_click = false;
				(*_viButtons2)->_frameX = 0;
			}
		}
	}
}

void RadioButton::buttonUp(int num)
{
	for (_viButtons = _vButtons.begin(); _viButtons != _vButtons.end(); ++_viButtons)
	{
		if ((*_viButtons)->_click)
		{
			(*_viButtons)->_onClick(num);
		}
	}
}

RadioButton::RadioButton()
{
}
