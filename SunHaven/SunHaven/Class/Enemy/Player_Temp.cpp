#include "Stdafx.h"
#include "Player_Temp.h"

HRESULT Player_Temp::init(void)
{
	_x = CENTER_X;
	_y = CENTER_Y + 200;

	_rcPlayer = RectMakeCenter(_x, _y, 50, 70);

    return S_OK;
}

void Player_Temp::release(void)
{
}

void Player_Temp::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 5.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 5.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 5.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 5.0f;
	}

	_rcPlayer = RectMakeCenter(_x, _y, 50, 70);
}

void Player_Temp::render(void)
{
	DrawRectMake(getMemDC(), _rcPlayer);
}
