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






	_swordSlash = IMAGEMANAGER->addImage("칼휘두르기",
		"Resources/Images/Player/IronSwordSlash.bmp",
		230, 132, true, RGB(255, 0, 255));
	_swordSlashAnim = new Animation;
	_swordSlashAnim->init(_swordSlash->getWidth(),
		_swordSlash->getHeight(),
		46, 66);

	_swordSlashAnim->setFPS(8);
	_swordSlashAnim->setPlayFrame(0, 4, false, false);

	_swordSlashRC = RectMakeCenter(_x, _y,
		_swordSlashAnim->getFrameWidth(),
		_swordSlashAnim->getFrameHeight());







	_jump = 5.5f;
	_isJump = false;



	_miniRC[0] = RectMake(_playerRC.left, _playerRC.top - 3, 3, 3);
	_miniRC[1] = RectMake(_playerRC.right + 3, _playerRC.top, 3, 3);
	_miniRC[2] = RectMake(_playerRC.right -3, _playerRC.top + 3, 3, 3);
	_miniRC[3] = RectMake(_playerRC.left-3, _playerRC.top, 3, 3);
	
	return S_OK;
}

void Player::release(void)
{
	_inven->release();

	_playerMoveAnim->release();
	SAFE_DELETE(_playerMoveAnim);
	
	_fireballAnim->release();
	SAFE_DELETE(_fireballAnim);
	
	_swordSlashAnim->release();
	SAFE_DELETE(_swordSlashAnim);
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
		_swordSlashAnim->setPlayFrame(0, 4, false, false);

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_x -= 220;
			_swordSlashAnim->AniStart();
		}

		if (stairCol == RGB(2, 62, 156))
		{
			_y -= _moveSpeed;
		}
		_playerMoveAnim->setPlayFrame(5, 9, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += _moveSpeed;
		int arr[5] = { 9,8,7,6,5 };
		_swordSlashAnim->setPlayFrame(arr, 5, false);

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_x += 220;
			_swordSlashAnim->AniStart();
		}

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

	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isJump = true;
	}

	if (_isJump)
	{
		if (_jump < -5.5f)
		{
			_isJump = false;
			_jump = 5.5f;
		}

		_y -= _jump;



		_jump -= 0.2f;
	}
	

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_swordSlashAnim->AniStart();
		cout << "칼";
	}

	if (_swordSlashAnim->isPlay())
	{
		cout << "발사";
	}


	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());


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
	_swordSlashAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void Player::render(void)
{

	DrawRectMake(getMemDC(), _playerRC);
	_fireball->aniRender(getMemDC(), _fireballRC.left, _fireballRC.top,
		_fireballAnim);
	_playerImage->aniRender(getMemDC(), _playerRC.left, _playerRC.top, _playerMoveAnim);

	if(_swordSlashAnim->isPlay())
	{
		_swordSlash->aniRender(getMemDC(), _swordSlashRC.left, _swordSlashRC.top,
			_swordSlashAnim);
	}

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
