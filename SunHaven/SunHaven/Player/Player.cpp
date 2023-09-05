#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(float x, float y)
{
	_x = x;
	_y = y;

	_inven = new Inventory;
	_inven->init();



	_playerImage = IMAGEMANAGER->addImage("임시플레이어",
		"Resources/Images/Player/kittywalk.bmp",
		960, 52, true, RGB(255, 0, 255));
	_playerMoveAnim = new Animation;
	_playerMoveAnim->init(_playerImage->getWidth(),
		_playerImage->getHeight(),
		48, 52);

	_playerMoveAnim->setFPS(4);

	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());

	_isCollisionLeft = _isCollisionRight =
		_isCollisionTop =_isCollisionBottom = false;
	_moveSpeed = 2.0f;







	_fireball = IMAGEMANAGER->addImage("파이어볼",
		"Resources/Images/Player/Fireball.bmp",
		288, 40, true, RGB(255, 0, 255));
	_fireballAnim = new Animation;
	_fireballAnim->init(_fireball->getWidth(),
		_fireball->getHeight(),
		48, 20);

	_fireballAnim->setFPS(8);

	_fireballRC = RectMakeCenter(_x, _y,
		_fireballAnim->getFrameWidth(),
		_fireballAnim->getFrameHeight());

	_fireballAnim->setPlayFrame(0, 5, false, true);







	_miniRC[0] = RectMake(_playerRC.left, _playerRC.top - 3, 3, 3);
	_miniRC[1] = RectMake(_playerRC.right + 3, _playerRC.top, 3, 3);
	_miniRC[2] = RectMake(_playerRC.right -3, _playerRC.top + 3, 3, 3);
	_miniRC[3] = RectMake(_playerRC.left-3, _playerRC.top, 3, 3);
	
	return S_OK;
}

void Player::release(void)
{
	_inven->release();
}

void Player::update(void)
{
	_inven->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) ||
		KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyDown(VK_UP) ||
		KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_playerMoveAnim->AniStart();
	}

	COLORREF stairCol =
		GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
			_x, _y);
	

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= _moveSpeed;
		if (stairCol == RGB(2, 62, 156))
		{
			_y -= _moveSpeed;
		}
		_playerMoveAnim->setPlayFrame(5, 9, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += _moveSpeed;
		if (stairCol == RGB(2, 62, 156))
		{
			_y += _moveSpeed;
		}
		_playerMoveAnim->setPlayFrame(15, 19, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= _moveSpeed;
		_playerMoveAnim->setPlayFrame(10, 14, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += _moveSpeed;
		_playerMoveAnim->setPlayFrame(0, 4, false, true);
	}
	else
	{
		_playerMoveAnim->AniStop();
	}

	

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_fireballAnim->AniStart();
	}

	if (_fireballAnim->isPlay())
	{
		cout << "발사";
		_fireballRC.left += 5;
		_fireballRC.right += 5;
	}


	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());

	_fireballRC = RectMakeCenter(_x, _y,
		_fireballAnim->getFrameWidth(),
		_fireballAnim->getFrameHeight());

	for (int i = _playerRC.left+4; i <= _playerRC.right-4; i++)
	{
		COLORREF collisionT =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				i, _playerRC.top);
		COLORREF collisionB =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				i, _playerRC.bottom);

		if (collisionT == RGB(255, 0, 255))
		{
			_isCollisionTop = true;
		}
		else
		{
			_isCollisionTop = false;
		}

		if (collisionB == RGB(255, 0, 255))
		{
			_isCollisionBottom = true;
		}
		else
		{
			_isCollisionBottom = false;
		}
	}

	for (int i = _playerRC.top + 4; i <= _playerRC.bottom - 4; i++)
	{
		COLORREF collisionL =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				_playerRC.left, i);

		COLORREF collisionR =
			GetPixel(IMAGEMANAGER->findImage("충돌")->getMemDC(),
				_playerRC.right, i);

		if (collisionL == RGB(255, 0, 255))
		{
			_isCollisionLeft = true;
			
		}
		else
		{
			_isCollisionLeft = false;
		}

		if (collisionR == RGB(255, 0, 255))
		{
			_isCollisionRight = true;
		}
		else
		{
			_isCollisionRight = false;
		}
	}

	

	if (_isCollisionLeft) _x += 2;
	if (_isCollisionRight) _x -= 2;
	if (_isCollisionTop) _y += 2;
	if (_isCollisionBottom) _y -= 2;

	_playerMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_fireballAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void Player::render(void)
{

	DrawRectMake(getMemDC(), _fireballRC);
	_fireball->aniRender(getMemDC(), _fireballRC.left, _fireballRC.top,
		_fireballAnim);
	_playerImage->aniRender(getMemDC(), _playerRC.left, _playerRC.top, _playerMoveAnim);

	_inven->render();
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
