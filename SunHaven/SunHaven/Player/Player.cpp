#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(float x, float y)
{
	_x = x;
	_y = y;

	/*_playerRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());*/

	_playerRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2,
		50,50);


	_miniRC[0] = RectMake(_playerRC.left, _playerRC.top - 3, 3, 3);
	_miniRC[1] = RectMake(_playerRC.right + 3, _playerRC.top, 3, 3);
	_miniRC[2] = RectMake(_playerRC.right -3, _playerRC.top + 3, 3, 3);
	_miniRC[3] = RectMake(_playerRC.left-3, _playerRC.top, 3, 3);

	return S_OK;
}

void Player::release(void)
{

}

void Player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_playerRC.left -= 3;
		_playerRC.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_playerRC.left += 3;
		_playerRC.right += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerRC.top -= 3;
		_playerRC.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_playerRC.top += 3;
		_playerRC.bottom += 3;
	}

	_miniRC[0] = RectMake(_playerRC.left, _playerRC.top - 5, 5, 5);
	_miniRC[1] = RectMake(_playerRC.right, _playerRC.top, 5, 5);
	_miniRC[2] = RectMake(_playerRC.right - 5, _playerRC.bottom, 5, 5);
	_miniRC[3] = RectMake(_playerRC.left - 5, _playerRC.bottom-5, 5, 5);

	for (int i = _miniRC[0].left; i < _miniRC[0].right; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("面倒")->getMemDC(),
				i, _miniRC[0].top);

		if (collision == RGB(255, 0, 255))
		{
			cout << "面倒1";
			_playerRC.top = _miniRC[0].bottom;
			_playerRC.bottom = _playerRC.top + 50;
		}
	}

	for (int i = _miniRC[1].top; i < _miniRC[1].bottom; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("面倒")->getMemDC(),
				 _miniRC[1].right,i);

		if (collision == RGB(255, 0, 255))
		{
			cout << "面倒2";
			_playerRC.right = _miniRC[1].left;
			_playerRC.left = _playerRC.right - 50;
		}
	}

	for (int i = _miniRC[2].left; i < _miniRC[2].right; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("面倒")->getMemDC(),
				i, _miniRC[2].bottom);

		if (collision == RGB(255, 0, 255))
		{
			cout << "面倒3";
			_playerRC.bottom = _miniRC[2].top;
			_playerRC.top = _playerRC.bottom - 50;
		}
	}

	for (int i = _miniRC[3].top; i < _miniRC[3].bottom; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("面倒")->getMemDC(),
				_miniRC[3].left, i);

		if (collision == RGB(255, 0, 255))
		{
			cout << "面倒4";
			_playerRC.left = _miniRC[3].right;
			_playerRC.right = _playerRC.left + 50;
		}
	}
}

void Player::render(void)
{
	DrawRectMake(getMemDC(), _playerRC);
	DrawRectMake(getMemDC(), _miniRC[0]);
	DrawRectMake(getMemDC(), _miniRC[1]);
	DrawRectMake(getMemDC(), _miniRC[2]);
	DrawRectMake(getMemDC(), _miniRC[3]);
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
