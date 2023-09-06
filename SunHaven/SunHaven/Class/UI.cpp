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
		FONTMANAGER->textOut(getMemDC(), _button._x, _button._y + _offsetY, "����ǹ��� ������ü", _fontSize, 100, _str, strlen(_str), _color);
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
			FONTMANAGER->textOut(getMemDC(), (*_viButtons)->_x, (*_viButtons)->_y + _offsetY, "����ǹ��� ������ü", _fontSize, 100, 
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

HRESULT UI::init(void)
{
	return S_OK;
}

HRESULT UI::init(string sceneName)
{
	_sceneName = sceneName;
	if (sceneName == "Farm")
	{
		_clock = IMAGEMANAGER->findImage("ClockUI");
		_cursor = IMAGEMANAGER->findImage("Cursor");
		_dateBar = IMAGEMANAGER->findGPImage("DateBar");
		_timeBar = IMAGEMANAGER->findGPImage("TimeBar");
		_upperRightBar = IMAGEMANAGER->findGPImage("UpperRightBar");
		_goldIcon = IMAGEMANAGER->findImage("GoldIcon");
		_ticketIcon = IMAGEMANAGER->findImage("TicketIcon");
		_orbIcon = IMAGEMANAGER->findImage("OrbIcon");
		_fishingNetIcon = IMAGEMANAGER->findImage("FishingNetIcon");
		_barnAnimalsIcon = IMAGEMANAGER->findImage("BarnAnimalsIcon");
		_skillTreeIcon = IMAGEMANAGER->findImage("SkillTreeIcon");
		_questBookIcon = IMAGEMANAGER->findImage("QuestBookIcon");
	}
	return S_OK;
}

void UI::release(void)
{
}

void UI::update(void)
{
	if (_sceneName == "Title")
	{

	}
}

void UI::render(void)
{
	if (_sceneName == "Farm")
	{
		_clock->render(getMemDC(), 20, 20, _clock->getWidth() * 1.5f, _clock->getHeight() * 1.5f, 0, 0, _clock->getWidth(), _clock->getHeight());
		_cursor->render(getMemDC(), _ptMouse.x, _ptMouse.y);
		_dateBar->GPFrameRender(getMemDC(), 130, 20, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		_dateBar->GPFrameRender(getMemDC(), 130, 55, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		_timeBar->GPFrameRender(getMemDC(), 130, 95, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		_upperRightBar->GPFrameRender(getMemDC(), WINSIZE_X - 666, 0, 1.5f, 1.5f, 0, 0, InterpolationModeNearestNeighbor, 0);
		FONTMANAGER->textOut(getMemDC(), 135, 25,"����ǹ��� ������ü", 20, 100, "�� 1����", strlen("�� 1����"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 135, 60,"����ǹ��� ������ü", 20, 100, "�Ͽ��� 1��", strlen("�Ͽ��� 1��"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), 135, 100,"����ǹ��� ������ü", 20, 100, "06:00AM", strlen("06:00AM"), RGB(255, 255, 255));
		_goldIcon->render(getMemDC(), WINSIZE_X - 300, 8, _goldIcon->getWidth() * 1.5f, _goldIcon->getHeight() * 1.5f, 0, 0, _goldIcon->getWidth(), _goldIcon->getHeight());
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 280, 8, "����ǹ��� ������ü", 14, 100, "1,669", strlen("1,669"), RGB(255, 255, 255));
		_orbIcon->render(getMemDC(), WINSIZE_X - 200, 8, _orbIcon->getWidth() * 1.5f, _orbIcon->getHeight() * 1.5f, 0, 0, _orbIcon->getWidth(), _orbIcon->getHeight());
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 180, 8, "����ǹ��� ������ü", 14, 100, "8", strlen("8"), RGB(255, 255, 255));
		_ticketIcon->render(getMemDC(), WINSIZE_X - 100, 4);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 75, 8, "����ǹ��� ������ü", 14, 100, "13", strlen("13"), RGB(255, 255, 255));
		_fishingNetIcon->render(getMemDC(), WINSIZE_X - 400, 4);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 375, 8, "����ǹ��� ������ü", 14, 100, "0/4", strlen("0/4"), RGB(255, 255, 255));
		_barnAnimalsIcon->render(getMemDC(), WINSIZE_X - 500, 4);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 470, 6, "����ǹ��� ������ü", 14, 100, "0/6", strlen("0/6"), RGB(255, 255, 255));
		_skillTreeIcon->render(getMemDC(), WINSIZE_X - _skillTreeIcon->getWidth() * 1.5, 50, _skillTreeIcon->getWidth() * 1.5, _skillTreeIcon->getHeight() * 1.5, 
			0, 0, _skillTreeIcon->getWidth(), _skillTreeIcon->getHeight());
		SetTextAlign(getMemDC(), TA_RIGHT);
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 40, 65, "����ǹ��� ������ü", 14, 100, "��ų Ʈ�� [K]", strlen("��ų Ʈ�� [K]"), RGB(255, 255, 255));
		_questBookIcon->render(getMemDC(), WINSIZE_X - _questBookIcon->getWidth() * 1.5 - 5, 95, _questBookIcon->getWidth() * 1.5, _questBookIcon->getHeight() * 1.5,
			0, 0, _questBookIcon->getWidth(), _questBookIcon->getHeight());
		FONTMANAGER->textOut(getMemDC(), WINSIZE_X - 40, 100, "����ǹ��� ������ü", 14, 100, "����Ʈ [L]", strlen("����Ʈ [L]"), RGB(255, 255, 255));
		SetTextAlign(getMemDC(), TA_LEFT);
	}
}
