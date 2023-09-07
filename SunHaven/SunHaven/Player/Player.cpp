#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(float x, float y)
{
	_x = x;
	_y = y;

	/*_playerRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());*/

	_playerRC = RectMakeCenter(_x, _y,
		50,50);

	return S_OK;
}

void Player::release(void)
{

}

void Player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 3.0f;

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 3.0f;
	}

	_playerRC = RectMakeCenter(_x, _y,
		50, 50);

	cout << _playerRC.left << endl;
}

void Player::render(void)
{
	DrawRectMake(getMemDC(), _playerRC);
}

void Player::UseTool()
{
}

void Player::UseFishingLod()
{
}

void Player::UseSword()
{
}

void Player::UseCrossBow()
{
}
