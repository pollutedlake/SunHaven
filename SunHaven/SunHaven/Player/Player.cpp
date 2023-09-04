#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(float x, float y)
{
	_x = x;
	_y = y;

	_playerImage = IMAGEMANAGER->addImage("임시플레이어",
		"Resources/Images/Player/kittywalk.bmp",
		960, 52, true, RGB(255, 0, 255));
	_playerMoveAnim = new Animation;
	_playerMoveAnim->init(_playerImage->getWidth(),
		_playerImage->getHeight(),
		48, 52);

	_playerMoveAnim->setFPS(7);

	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());

	/*_playerRC = RectMakeCenter(_x,_y,
		50,50);*/


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
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) ||
		KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyDown(VK_UP) ||
		KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_playerMoveAnim->AniStart();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3;
		_playerMoveAnim->setPlayFrame(5, 9, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3;
		_playerMoveAnim->setPlayFrame(15, 19, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 3;
		_playerMoveAnim->setPlayFrame(10, 14, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 3;
		_playerMoveAnim->setPlayFrame(0, 4, false, true);
	}
	else
	{
		_playerMoveAnim->AniStop();
	}

	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());


	for (int i = _playerRC.left; i < _playerRC.right; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				i, _playerRC.top);

		if (collision == RGB(255, 0, 255))
		{
			cout << "충돌1";
		}
	}

	for (int i = _playerRC.top; i < _playerRC.bottom; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				_playerRC.right,i);

		if (collision == RGB(255, 0, 255))
		{
			cout << "충돌2";
		}
	}

	for (int i = _playerRC.left; i < _playerRC.right; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				i, _playerRC.bottom);

		if (collision == RGB(255, 0, 255))
		{
			cout << "충돌3";
		}
	}

	for (int i = _playerRC.top; i < _playerRC.bottom; i++)
	{
		COLORREF collision =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				_playerRC.left, i);

		if (collision == RGB(255, 0, 255))
		{
			cout << "충돌4";
		}
	}


	_playerMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void Player::render(void)
{
	//DrawRectMake(getMemDC(), _playerRC);

	_playerImage->aniRender(getMemDC(), _playerRC.left, _playerRC.top, _playerMoveAnim);

	/*DrawRectMake(getMemDC(), _miniRC[0]);
	DrawRectMake(getMemDC(), _miniRC[1]);
	DrawRectMake(getMemDC(), _miniRC[2]);
	DrawRectMake(getMemDC(), _miniRC[3]);*/
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
