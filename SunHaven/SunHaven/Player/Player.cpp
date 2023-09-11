#include "Stdafx.h"
#include "Player.h"
#include "../Class/Object/ObjectManager.h"

HRESULT Player::init(float x, float y, string collisionMapKey)
{
	_x = x;
	_y = y;

	_collisionMap = IMAGEMANAGER->findImage(collisionMapKey);


	_skill = new SkillManager;
	_skill->init();

	_inven = new Inventory;
	_inven->init();

	_eTools = eTools::SICKLE;


	_playerImage = IMAGEMANAGER->addImage("ÀÓ½ÃÇÃ·¹ÀÌ¾î",
		"Resources/Images/Player/kittywalk.bmp",
		960, 52, true, RGB(255, 0, 255));
	_playerMoveAnim = new Animation;
	_playerMoveAnim->init(_playerImage->getWidth(),
		_playerImage->getHeight(),
		48, 52);

	_playerMoveAnim->setFPS(8);

	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());

	_isCollisionLeft = _isCollisionRight =
		_isCollisionTop =_isCollisionBottom = false;
	_moveSpeed = 3.0f;


	_fireBeam = IMAGEMANAGER->addImage("ÆÄÀÌ¾îºö",
		"Resources/Images/Skill/combat/FirebeamA.bmp",
		100, 50, true, RGB(255, 0, 255));
	_firebeamRC = RectMakeCenter(_x, _y, 50, 50);


	_fireball = IMAGEMANAGER->addImage("ÆÄÀÌ¾îº¼",
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




	IMAGEMANAGER->addImage("Ä® À§¾Æ·¡ ÈÖµÎ¸£±â",
		"Resources/Images/Player/IronSwordSlashUpDown.bmp",
		330, 90, true, RGB(255, 0, 255));

	_swordSlash = IMAGEMANAGER->addImage("Ä®ÈÖµÎ¸£±â",
		"Resources/Images/Player/IronSwordSlash.bmp",
		230, 132, true, RGB(255, 0, 255));

	_swordSlashAnim = new Animation;
	_swordSlashAnim->init(_swordSlash->getWidth(),
		_swordSlash->getHeight(),
		46, 66);

	_swordSlashUpDownAnim = new Animation;
	_swordSlashUpDownAnim->init(_swordSlash->getWidth(),
		_swordSlash->getHeight(),
		66, 45);

	_swordAnim = _swordSlashAnim;

	_swordAnim->setFPS(10);
	_swordAnim->setPlayFrame(0, 4, false, false);

	_swordSlashRC = RectMakeCenter(_x, _y,
		_swordAnim->getFrameWidth(),
		_swordAnim->getFrameHeight());



	



	_jump = 5.5f;
	_isJump = false;


	_playerState.playerName=INIDATAMANAGER->loadDataString("tempINIFile", "commonState", "playerName");
	_playerState.HP = INIDATAMANAGER->loadDataInteger("tempINIFile", "commonState", "HP");
	_playerState.MP = INIDATAMANAGER->loadDataInteger("tempINIFile", "commonState", "MP");
	_playerState.gold = INIDATAMANAGER->loadDataInteger("tempINIFile", "commonState", "Gold");
	
	_playerState.HPRecoveryPerSec = (float)_playerState.HP / 1500;
	_playerState.MPRecoveryPerSec = (float)_playerState.MP / 50;

	_playerState.attackDamage = INIDATAMANAGER->loadDataInteger("tempINIFile", "combatState", "attackDamage");
	_playerState.spellDamage = INIDATAMANAGER->loadDataInteger("tempINIFile", "combatState", "spellDamage");
	_playerState.defence = INIDATAMANAGER->loadDataInteger("tempINIFile", "combatState", "defence");
	

	
	_miniRC[0] = RectMake(_playerRC.left, _playerRC.top - 3, 3, 3);
	_miniRC[1] = RectMake(_playerRC.right + 3, _playerRC.top, 3, 3);
	_miniRC[2] = RectMake(_playerRC.right -3, _playerRC.top + 3, 3, 3);
	_miniRC[3] = RectMake(_playerRC.left-3, _playerRC.top, 3, 3);
	


	return S_OK;
}

void Player::release(void)
{
	_inven->release();

	_skill->release();
	SAFE_DELETE(_skill);

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

	//cout << _ptMouse.x << ", " << _ptMouse.y << endl;

	//COLORREF waterCol =
	//	GetPixel(_collisionMap->getMemDC(),
	//		_ptMouse.x, _ptMouse.y);
	//int r = GetRValue(waterCol);
	//int g = GetGValue(waterCol);
	//int b = GetBValue(waterCol);
	//cout << r << ", " << g << ", " << b << endl;

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) ||
		KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyDown(VK_UP) ||
		KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_playerMoveAnim->AniStart();
	}

	COLORREF stairCol =
		GetPixel(IMAGEMANAGER->findImage("Ãæµ¹")->getMemDC(),
			_x, _y);
	

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= _moveSpeed;
		_swordSlash = IMAGEMANAGER->findImage("Ä®ÈÖµÎ¸£±â");
		_swordAnim = _swordSlashAnim;
		_swordAnim->setPlayFrame(0, 4, false, false);

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
		_swordSlash = IMAGEMANAGER->findImage("Ä®ÈÖµÎ¸£±â");
		_swordAnim = _swordSlashAnim;
		int arr[5] = { 9,8,7,6,5 };
		_swordAnim->setPlayFrame(arr, 5, false);

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
		_swordSlash = IMAGEMANAGER->findImage("Ä® À§¾Æ·¡ ÈÖµÎ¸£±â");
		_swordSlashUpDownAnim->setPlayFrame(0, 4, false, false);
		_swordAnim = _swordSlashUpDownAnim;

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_y -= 220;
		}
		_playerMoveAnim->setPlayFrame(10, 14, false, true);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += _moveSpeed;
		_swordSlash = IMAGEMANAGER->findImage("Ä® À§¾Æ·¡ ÈÖµÎ¸£±â");
		int arr[5] = { 9,8,7,6,5 };
		_swordSlashUpDownAnim->setPlayFrame(arr, 5, false);
		_swordAnim = _swordSlashUpDownAnim;

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_y += 220;
		}
		_playerMoveAnim->setPlayFrame(0, 4, false, true);
	}
	else
	{
		_playerMoveAnim->AniStop();
	}

	cout << _swordAnim->getNowPlayIdx() << endl;

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
		_swordAnim->AniStart();
	}

	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());


	if (_collisionMap != nullptr)
	{
		for (int i = _playerRC.left + 4; i <= _playerRC.right - 4; i++)
		{
			COLORREF collisionT =
				GetPixel(_collisionMap->getMemDC(),
					i, _playerRC.top);
			COLORREF collisionB =
				GetPixel(_collisionMap->getMemDC(),
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
				GetPixel(_collisionMap->getMemDC(),
					_playerRC.left, i);

			COLORREF collisionR =
				GetPixel(_collisionMap->getMemDC(),
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
	}

	if (KEYMANAGER->isStayKeyDown('1'))
	{
		_eTools = eTools::SICKLE;
	}
	if (KEYMANAGER->isStayKeyDown('2'))
	{
		_eTools = eTools::AXE;
	}
	if (KEYMANAGER->isStayKeyDown('3'))
	{
		_eTools = eTools::PICKAXE;
	}

	if (KEYMANAGER->isStayKeyDown('U'))
	{
		_firebeamRC.right += 10;
		offsetX -= 10;
	}
	else
	{
		_firebeamRC = RectMakeCenter(_x, _y, 50, 50);
	}


	_skill->update();
	

	if (_isCollisionLeft) _x += _moveSpeed;
	if (_isCollisionRight) _x -= _moveSpeed;
	if (_isCollisionTop) _y += _moveSpeed;
	if (_isCollisionBottom) _y -= _moveSpeed;

	_playerMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_fireballAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_swordAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void Player::render(void)
{
	_fireball->aniRender(getMemDC(), _fireballRC.left, _fireballRC.top,
		_fireballAnim);


	if (KEYMANAGER->isStayKeyDown('U'))
	{
		_fireBeam->loopRender(getMemDC(), &_firebeamRC,
			offsetX, 0);
	}

	_playerImage->aniRender(getMemDC(), _playerRC.left, _playerRC.top, _playerMoveAnim);

	DrawRectMake(getMemDC(), _swordSlashRC);
	if(_swordAnim->isPlay())
	{
		_swordSlash->aniRender(getMemDC(), _swordSlashRC.left, _swordSlashRC.top,
			_swordAnim);
	}


	_inven->render();
	
	if(KEYMANAGER->isToggleKey('K'))
		_skill->render();

	/*DrawRectMake(getMemDC(), _miniRC[0]);
	DrawRectMake(getMemDC(), _miniRC[1]);
	DrawRectMake(getMemDC(), _miniRC[2]);
	DrawRectMake(getMemDC(), _miniRC[3]);*/
}

void Player::UseTool(ObjectManager* object)
{
	RECT temp;

	for (int i = 0; i < object->getObjectList().size(); i++)
	{
		if (object->getObjectList()[i]->getType() / 2 == 0
			&& _eTools == eTools::SICKLE)
		{
			if (IntersectRect(&temp,
				&object->getObjectList()[i]->getRC(),
				&_swordSlashRC)
				&& _swordSlashAnim->getNowPlayIdx()==1)
			{
				object->getObjectList()[i]->setHP(1);
			}

		}

		else if (object->getObjectList()[i]->getType() / 2 == 1
			&& _eTools == eTools::AXE)
		{
			if (IntersectRect(&temp,
				&object->getObjectList()[i]->getRC(),
				&_swordSlashRC)
				&& _swordSlashAnim->getNowPlayIdx() == 1)
			{
				object->getObjectList()[i]->setHP(1);
			}

		}

		else if (object->getObjectList()[i]->getType() / 2 == 2
			&& _eTools == eTools::PICKAXE)
		{
			if (IntersectRect(&temp,
				&object->getObjectList()[i]->getRC(),
				&_swordSlashRC)
				&& _swordSlashAnim->getNowPlayIdx() == 1)
			{
				object->getObjectList()[i]->setHP(1);
			}

		}
	}
}

void Player::UseFishingLod()
{
	
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		if (GetPixel(_collisionMap->getMemDC(), _ptMouse.x, _ptMouse.y)
			== RGB(255, 0, 0))
		{
			cout << "³¬½ÃÇÏ°Ô?" << endl;
		}
	}
}

void Player::UseSword()
{

}

void Player::UseCrossBow()
{

}

void Player::ObjectCollision(ObjectManager* object)
{
	for (int i = 0; i < object->getObjectList().size(); i++)
	{
		RECT temp;

		if (IntersectRect(&temp,
			&_playerRC,
			&object->getObjectList()[i]->getRC()))
		{
			//_x -= _moveSpeed;
			cout << "Ãæµ¹µÊ" << endl;
		}
	}
}


