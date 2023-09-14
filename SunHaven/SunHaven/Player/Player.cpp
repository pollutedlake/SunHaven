#include "Stdafx.h"
#include "Player.h"
#include "../Class/Object/ObjectManager.h"
#include "../Class/Inventory.h"

HRESULT Player::init(float x, float y, string collisionMapKey)
{
	_x = x;
	_y = y;

	_collisionMap = IMAGEMANAGER->findImage(collisionMapKey);

	_skill = new SkillManager;
	_skill->init();

	_eTools = eTools::SICKLE;

	_fireBall = new Fireball;
	_fireBall->init(50, 500);

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

	_playertoCameraRC = RectMakeCenter(_cx, _cy,
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




	/*IMAGEMANAGER->addImage("Ä® À§¾Æ·¡ ÈÖµÎ¸£±â",
		"Resources/Images/Player/IronSwordSlashUpDown.bmp",
		330, 90, true, RGB(255, 0, 255));*/

	_swordSlash = IMAGEMANAGER->addImage("Ä®ÈÖµÎ¸£±â",
		"Resources/Images/Player/iron_sword_slash.bmp",
		4032, 168, true, RGB(255, 0, 255));

	_swordSwingAnim = new Animation;
	_swordSwingAnim->init(_swordSlash->getWidth(),
		_swordSlash->getHeight(),
		168, 168);

	_swordSwingRC = RectMakeCenter(_x, _y,
		_swordSwingAnim->getFrameWidth(),
		_swordSwingAnim->getFrameHeight());

	_swordSwingAnim->setFPS(10);
	_swordSwingAnim->setPlayFrame(0, 5, false, false);

	//_swordSlashAnim = new Animation;
	//_swordSlashAnim->init(_swordSlash->getWidth(),
	//	_swordSlash->getHeight(),
	//	46, 66);

	//_swordSlashUpDownAnim = new Animation;
	//_swordSlashUpDownAnim->init(_swordSlash->getWidth(),
	//	_swordSlash->getHeight(),
	//	66, 45);

	//_swordAnim = _swordSlashAnim;

	//_swordAnim->setFPS(10);
	//_swordAnim->setPlayFrame(0, 4, false, false);

	//_swordSlashRC = RectMakeCenter(_x, _y,
	//	_swordAnim->getFrameWidth(),
	//	_swordAnim->getFrameHeight());

	



	//=============================================//



	_axeSwing = IMAGEMANAGER->addImage("µµ³¢ÈÖµÎ¸£±â",
		"Resources/Images/Player/rustyaxeswing.bmp",
		3360, 168, true, RGB(255, 0, 255));

	_axeSwingAnim = new Animation;
	_axeSwingAnim->init(_axeSwing->getWidth(),
		_axeSwing->getHeight(),
		168, 168);

	_axeSwingAnim->setFPS(10);
	_axeSwingAnim->setPlayFrame(5, 9, false, false);

	_axeSwingRC = RectMakeCenter(_x, _y,
		_axeSwingAnim->getFrameWidth(),
		_axeSwingAnim->getFrameHeight());

	//=============================================//

	_pickaxeSwing = IMAGEMANAGER->addImage("°î±ªÀÌÈÖµÎ¸£±â",
		"Resources/Images/Player/rustypickaxeswing.bmp",
		960, 101, true, RGB(255, 0, 255));

	_pickaxeSwingAnim = new Animation;
	_pickaxeSwingAnim->init(_pickaxeSwing->getWidth(),
		_pickaxeSwing->getHeight(),
		60, 101);

	_pickaxeSwingAnim->setFPS(10);
	_pickaxeSwingAnim->setPlayFrame(5, 9, false, false);

	_pickaxeSwingRC = RectMakeCenter(_x, _y,
		_pickaxeSwingAnim->getFrameWidth(),
		_pickaxeSwingAnim->getFrameHeight());

	//=============================================//

	_hoeSwing = IMAGEMANAGER->addImage("±ªÀÌÈÖµÎ¸£±â",
		"Resources/Images/Player/rustyhoe.bmp",
		960, 100, true, RGB(255, 0, 255));

	_hoeSwingAnim = new Animation;
	_hoeSwingAnim->init(_hoeSwing->getWidth(),
		_hoeSwing->getHeight(),
		60, 100);

	_hoeSwingAnim->setFPS(10);
	_hoeSwingAnim->setPlayFrame(5, 9, false, false);

	_hoeSwingRC = RectMakeCenter(_x, _y,
		_hoeSwingAnim->getFrameWidth(),
		_hoeSwingAnim->getFrameHeight());


	//=============================================//

	_scytheSwing = IMAGEMANAGER->addImage("³´ÈÖµÎ¸£±â",
		"Resources/Images/Player/scytheswing.bmp",
		3360, 168, true, RGB(255, 0, 255));

	_scytheSwingAnim = new Animation;
	_scytheSwingAnim->init(_scytheSwing->getWidth(),
		_scytheSwing->getHeight(),
		168, 168);

	_scytheSwingAnim->setFPS(10);
	_scytheSwingAnim->setPlayFrame(5, 9, false, false);

	_scytheSwingRC = RectMakeCenter(_x, _y,
		_scytheSwingAnim->getFrameWidth(),
		_scytheSwingAnim->getFrameHeight());


	//=============================================//

	_fishingLod = IMAGEMANAGER->addImage("³¬½ÃÇÏ±â",
		"Resources/Images/Player/fishing_rod.bmp",
		1680, 60, true, RGB(255, 0, 255));

	_fishingLodAnim = new Animation;
	_fishingLodAnim->init(_fishingLod->getWidth(),
		_fishingLod->getHeight(),
		60, 60);

	_fishingLodAnim->setFPS(10);
	_fishingLodAnim->setPlayFrame(7, 13, false, false);

	_fishingLodRC = RectMakeCenter(_x, _y,
		_fishingLodAnim->getFrameWidth(),
		_fishingLodAnim->getFrameHeight());


	//=============================================//

	_fishingBorder = IMAGEMANAGER->addImage("ÆÛÆåÆ®Á¸Å×µÎ¸®",
		"Resources/Images/Player/fishing_border.bmp",
		176, 48, true, RGB(255, 0, 255));
	_fishingCursor = IMAGEMANAGER->addImage("ÆÛÆåÆ®Á¸Ä¿¼­",
		"Resources/Images/Player/fishing_cursor.bmp",
		27, 42, true, RGB(255, 0, 255));
	_fishingGreatZone = IMAGEMANAGER->addImage("±×·¹ÀÌÆ®Á¸",
		"Resources/Images/Player/fishing_greatzone.bmp",
		10, 20, true, RGB(255, 0, 255));
	_fishingPerfectZone = IMAGEMANAGER->addImage("ÆÛÆåÆ®Á¸",
		"Resources/Images/Player/fishing_perfectzone.bmp",
		10, 20, true, RGB(255, 0, 255));


	_fishingBorderRC = RectMakeCenter(CENTER_X, CENTER_Y + 50,
		_fishingBorder->getWidth(),
		_fishingBorder->getHeight());

	_fishingCursorRC = RectMakeCenter(CENTER_X, CENTER_Y + 50,
		_fishingCursor->getWidth(),
		_fishingCursor->getHeight());

	_fishingGreatZoneRC = RectMakeCenter(CENTER_X, CENTER_Y + 50,
		_fishingGreatZone->getWidth(),
		_fishingGreatZone->getHeight());

	_fishingPerfectZoneRC = RectMakeCenter(CENTER_X, CENTER_Y + 50,
		_fishingPerfectZone->getWidth(),
		_fishingPerfectZone->getHeight());

	//=============================================//


	_jump = 5.5f;
	_isJump = false;
	_isLeft = false;
	_isFishing = false;
	_isSuccessFishing = false;

	_playerState.playerName=INIDATAMANAGER->loadDataString("tempINIFile", "commonState", "playerName");
	_playerState.HP = INIDATAMANAGER->loadDataInteger("tempINIFile", "commonState", "HP");
	_playerState.MP = INIDATAMANAGER->loadDataInteger("tempINIFile", "commonState", "MP");
	_playerState.gold = INIDATAMANAGER->loadDataInteger("tempINIFile", "commonState", "Gold");
	
	_playerState.HPRecoveryPerSec = (float)_playerState.HP / 1500;
	_playerState.MPRecoveryPerSec = (float)_playerState.MP / 50;

	_playerState.attackDamage = INIDATAMANAGER->loadDataInteger("tempINIFile", "combatState", "attackDamage");
	_playerState.spellDamage = INIDATAMANAGER->loadDataInteger("tempINIFile", "combatState", "spellDamage");
	_playerState.defence = INIDATAMANAGER->loadDataInteger("tempINIFile", "combatState", "defence");
	
	_toolImage = _scytheSwing;
	_toolAnim = _scytheSwingAnim;
	_toolAnimRC = _scytheSwingRC;

	_miniRC[0] = RectMake(_playerRC.left, _playerRC.top - 3, 3, 3);
	_miniRC[1] = RectMake(_playerRC.right + 3, _playerRC.top, 3, 3);
	_miniRC[2] = RectMake(_playerRC.right -3, _playerRC.top + 3, 3, 3);
	_miniRC[3] = RectMake(_playerRC.left-3, _playerRC.top, 3, 3);
	
	_isLoop = false;

	return S_OK;
}

void Player::release(void)
{
	//_inven->release();
	_fireBall->release();
	SAFE_DELETE(_fireBall);

	_skill->release();
	SAFE_DELETE(_skill);

	_playerMoveAnim->release();
	SAFE_DELETE(_playerMoveAnim);
	
	_fireballAnim->release();
	SAFE_DELETE(_fireballAnim);

	_swordSlashAnim->release();
	SAFE_DELETE(_swordSlashAnim);

	_axeSwingAnim->release();
	SAFE_DELETE(_axeSwingAnim);
}

void Player::update(void)
{
	//_inven->update();

	if (KEYMANAGER->isOnceKeyDown('W') ||
		KEYMANAGER->isOnceKeyDown('S') ||
		KEYMANAGER->isOnceKeyDown('A') ||
		KEYMANAGER->isOnceKeyDown('D'))
	{
		_playerMoveAnim->AniStart();
	}

	COLORREF stairCol =
		GetPixel(_collisionMap->getMemDC(),
			_x, _y);

	if (!_toolAnim->isPlay() || !_isFishing)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_isLeft = true;
			_x -= _moveSpeed;/*
			_swordSlash = IMAGEMANAGER->findImage("Ä®ÈÖµÎ¸£±â");
			_swordAnim = _swordSlashAnim;
			_swordAnim->setPlayFrame(0, 4, false, false);*/
			_swordSwingAnim->setPlayFrame(18, 23, false, false);

			for (int i = 0; i < 4; i++)
			{
				axeSwingAnimArr[i] = i + 15;
				pickaxeSwingAnimArr[i] = i + 12;
				hoeSwingAnimArr[i] = i + 12;
				scytheSwingAnimArr[i] = i + 15;
			}

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
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_isLeft = false;
			_x += _moveSpeed;/*
			_swordSlash = IMAGEMANAGER->findImage("Ä®ÈÖµÎ¸£±â");
			_swordAnim = _swordSlashAnim;
			int arr[5] = { 9,8,7,6,5 };
			_swordAnim->setPlayFrame(arr, 5, false);*/

			for (int i = 0; i < 4; i++)
			{
				axeSwingAnimArr[i] = i + 5;
				pickaxeSwingAnimArr[i] = i + 4;
				hoeSwingAnimArr[i] = i + 4;
				scytheSwingAnimArr[i] = i + 5;
			}

			_swordSwingAnim->setPlayFrame(6, 11, false, false);

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
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			_y -= _moveSpeed;/*
			_swordSlash = IMAGEMANAGER->findImage("Ä® À§¾Æ·¡ ÈÖµÎ¸£±â");
			_swordSlashUpDownAnim->setPlayFrame(0, 4, false, false);
			_swordAnim = _swordSlashUpDownAnim;*/

			_swordSwingAnim->setPlayFrame(12, 17, false, false);

			for (int i = 0; i < 4; i++)
			{
				axeSwingAnimArr[i] = i + 10;
				pickaxeSwingAnimArr[i] = i + 8;
				hoeSwingAnimArr[i] = i + 8;
				scytheSwingAnimArr[i] = i + 10;
			}

			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_y -= 220;
			}
			_playerMoveAnim->setPlayFrame(10, 14, false, true);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_y += _moveSpeed;/*
			_swordSlash = IMAGEMANAGER->findImage("Ä® À§¾Æ·¡ ÈÖµÎ¸£±â");
			int arr[5] = { 9,8,7,6,5 };
			_swordSlashUpDownAnim->setPlayFrame(arr, 5, false);
			_swordAnim = _swordSlashUpDownAnim;*/
			_swordSwingAnim->setPlayFrame(0, 5, false, false);

			for (int i = 0; i < 4; i++)
			{
				axeSwingAnimArr[i] = i;
				pickaxeSwingAnimArr[i] = i;
				hoeSwingAnimArr[i] = i;
				scytheSwingAnimArr[i] = i;
			}


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
	}


	_axeSwingAnim->setPlayFrame(axeSwingAnimArr, 4, _isLoop);
	_pickaxeSwingAnim->setPlayFrame(pickaxeSwingAnimArr, 4, _isLoop);
	_hoeSwingAnim->setPlayFrame(hoeSwingAnimArr, 4, _isLoop);
	_scytheSwingAnim->setPlayFrame(scytheSwingAnimArr, 4, _isLoop);



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
		//_swordAnim->AniStart();
		_swordSwingAnim->AniStart();
	}





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

			_isCollisionTop =
				collisionT == RGB(255, 0, 255) ? true : false;
			_isCollisionBottom =
				collisionB == RGB(255, 0, 255) ? true : false;
		}

		for (int i = _playerRC.top + 4; i <= _playerRC.bottom - 4; i++)
		{
			COLORREF collisionL =
				GetPixel(_collisionMap->getMemDC(),
					_playerRC.left, i);

			COLORREF collisionR =
				GetPixel(_collisionMap->getMemDC(),
					_playerRC.right, i);

			_isCollisionLeft =
				collisionL == RGB(255, 0, 255) ? true : false;
			_isCollisionRight =
				collisionR == RGB(255, 0, 255) ? true : false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_eTools = eTools::SICKLE;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_eTools = eTools::HOE;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_eTools = eTools::AXE;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_eTools = eTools::PICKAXE;
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_eTools = eTools::FISHINGLOD;
	}


	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		_fireBall->fire(_x, _y, _isLeft);
	}
	_fireBall->update(WINSIZE_X / 2 + _x - _cx, WINSIZE_Y / 2 + _y - _cy);



	if (KEYMANAGER->isStayKeyDown('U'))
	{
		_firebeamRC.right += 10;
		offsetX -= 10;
	}
	else
	{
		_firebeamRC = RectMakeCenter(_x, _y, 50, 50);
	}

	if (_isFishing)
	{
		Fishing();
	}

	_skill->update();

	_playerRC = RectMakeCenter(_x, _y,
		_playerMoveAnim->getFrameWidth(),
		_playerMoveAnim->getFrameHeight());

	if (_isCollisionLeft) _x += _moveSpeed;
	if (_isCollisionRight) _x -= _moveSpeed;
	if (_isCollisionTop) _y += _moveSpeed;
	if (_isCollisionBottom) _y -= _moveSpeed;


	_playerMoveAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_fireballAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	//_swordAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_swordSwingAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_axeSwingAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_pickaxeSwingAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_hoeSwingAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_scytheSwingAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_fishingLodAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	//cout << _fishingLodAnim->getNowPlayIdx() << endl;
}

void Player::render(void)
{


	_fireBall->render();

	if (KEYMANAGER->isStayKeyDown('U'))
	{
		_fireBeam->loopRender(getMemDC(), &_firebeamRC,
			offsetX, 0);
	}

	_playerImage->aniRender(getMemDC(),
		_playertoCameraRC.left, _playertoCameraRC.top, _playerMoveAnim);

	if(_swordSwingAnim->isPlay())
	{
		_swordSlash->aniRender(getMemDC(), _swordSwingRC.left, _swordSwingRC.top,
			_swordSwingAnim);
	}

	if (_isFishing)
	{
		_fishingLod->aniRender(getMemDC(), _fishingLodRC.left, _fishingLodRC.top,
			_fishingLodAnim);
	}

	if (_toolAnim->isPlay())
	{
		_toolImage->aniRender(getMemDC(), _toolAnimRC.left, _toolAnimRC.top,
			_toolAnim);
	}

	
	if (_isFishing)
	{
		_fishingBorder->render(getMemDC(), _fishingBorderRC.left,
			_fishingBorderRC.top);
		_fishingGreatZone->render(getMemDC(), _fishingGreatZoneRC.left,
			_fishingGreatZoneRC.top,
			_fishingGreatZoneRC.right - _fishingGreatZoneRC.left, 20,
			0, 0, 10, 20);
		_fishingPerfectZone->render(getMemDC(), _fishingPerfectZoneRC.left,
			_fishingPerfectZoneRC.top,
			(_fishingPerfectZoneRC.right - _fishingPerfectZoneRC.left), 20,
			0, 0, 10, 20);
		_fishingCursor->render(getMemDC(), _fishingCursorRC.left,
			_fishingCursorRC.top);
	}

	if(KEYMANAGER->isToggleKey('K'))
		_skill->render();
}

void Player::MouseOver(ObjectManager* object, POINT point)
{
	for (int i = 0; i < object->getObjectList().size(); i++)
	{
		if (PtInRect(&object->getObjectList()[i]->getCollisionRC(),
			point) &&
			object->getObjectList()[i]->getType() > 1)
		{
			if (getDistance(_cx, _cy, point.x, point.y) < OBJECT_RANGE)
			{
				IMAGEMANAGER->render("¿ÀºêÁ§Æ® ¼±ÅÃ", getMemDC(),
					object->getObjectList()[i]->getCollisionRC().left,
					object->getObjectList()[i]->getCollisionRC().top);
			}
		}
	}
}

void Player::UseTool(ObjectManager* object, POINT point)
{
	RECT temp;
	float updown = point.y - _cy;
	float leftright = point.x - _cx;

	switch (_eTools)
	{
	case eTools::SICKLE:
		_toolImage = _scytheSwing;
		_toolAnim = _scytheSwingAnim;
		_toolAnimRC = _scytheSwingRC;
		break;

	case eTools::HOE:
		_toolImage = _hoeSwing;
		_toolAnim = _hoeSwingAnim;
		_toolAnimRC = _hoeSwingRC;
		break;

	case eTools::AXE:
		_toolImage = _axeSwing;
		_toolAnim = _axeSwingAnim;
		_toolAnimRC = _axeSwingRC;
		break;

	case eTools::PICKAXE:
		_toolImage = _pickaxeSwing;
		_toolAnim = _pickaxeSwingAnim;
		_toolAnimRC = _pickaxeSwingRC;
		break;

	default:
		break;
	}

	if (updown < 0 && abs(updown) > leftright)
	{
		for (int i = 0; i < 4; i++)
		{
			axeSwingAnimArr[i] = i + 10;
			pickaxeSwingAnimArr[i] = i + 8;
			hoeSwingAnimArr[i] = i + 8;
			scytheSwingAnimArr[i] = i + 10;
		}
		_playerMoveAnim->setPlayFrame(10, 14, false, true);
	}
	else if (updown > 0 && abs(leftright) < updown)
	{
		for (int i = 0; i < 4; i++)
		{
			axeSwingAnimArr[i] = i;
			pickaxeSwingAnimArr[i] = i;
			hoeSwingAnimArr[i] = i;
			scytheSwingAnimArr[i] = i;
		}
		_playerMoveAnim->setPlayFrame(0, 4, false, true);
	}
	else if (leftright < 0)
	{
		for (int i = 0; i < 4; i++)
		{
			axeSwingAnimArr[i] = i + 15;
			pickaxeSwingAnimArr[i] = i + 12;
			hoeSwingAnimArr[i] = i + 12;
			scytheSwingAnimArr[i] = i + 15;
		}
		_playerMoveAnim->setPlayFrame(5, 9, false, true);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			axeSwingAnimArr[i] = i + 5;
			pickaxeSwingAnimArr[i] = i + 4;
			hoeSwingAnimArr[i] = i + 4;
			scytheSwingAnimArr[i] = i + 5;
		}
		_playerMoveAnim->setPlayFrame(15, 19, false, true);
	}

	_axeSwingAnim->setPlayFrame(axeSwingAnimArr, 4, _isLoop);
	_pickaxeSwingAnim->setPlayFrame(pickaxeSwingAnimArr, 4, _isLoop);
	_hoeSwingAnim->setPlayFrame(hoeSwingAnimArr, 4, _isLoop);
	_scytheSwingAnim->setPlayFrame(scytheSwingAnimArr, 4, _isLoop);

	
	_toolAnim->AniStart();


	for (int i = 0; i < object->getObjectList().size(); i++)
	{
		if (object->getObjectList()[i]->getType() / 2 == 0
			&& _eTools == eTools::SICKLE)
		{
			if (IntersectRect(&temp,
				&object->getObjectList()[i]->getCollisionRC(),
				&_toolAnimRC)
				&& _toolAnim->getNowPlayIdx() >= 0)
			{
				// SD : Ç®º£´Â ¼Ò¸®
				object->getObjectList()[i]->setHP(1);
			}
		}

		else if (object->getObjectList()[i]->getType() / 2 == 1
			&& _eTools == eTools::AXE)
		{
			if (PtInRect(&object->getObjectList()[i]->getCollisionRC(),
				point)
				&& _toolAnim->getNowPlayIdx() >= 0
				&& getDistance(_cx, _cy, point.x, point.y) < OBJECT_RANGE)
			{
				// SD : ³ª¹« º£´Â ¼Ò¸®
				object->getObjectList()[i]->setHP(10, _x);
			}
		}

		else if (object->getObjectList()[i]->getType() / 2 == 2
			&& _eTools == eTools::PICKAXE
			&& getDistance(_cx, _cy, point.x, point.y) < OBJECT_RANGE)
		{
			if (PtInRect(&object->getObjectList()[i]->getCollisionRC(),
				point)
				&& _toolAnim->getNowPlayIdx() >= 0)
			{
				// SD : µ¹Ä³´Â ¼Ò¸®
				object->getObjectList()[i]->setHP(5);
			}
		}
	}
}

void Player::UseFishingLod(POINT point)
{
	float updown = point.y - _y;
	float leftright = point.x - _x;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (updown < 0 && abs(updown) > leftright)
		{
			_playerMoveAnim->setPlayFrame(10, 14, false, true);
			_fishingLodAnim->setPlayFrame(0, 6, false, false);
		}
		else if (updown > 0 && abs(leftright) < updown)
		{
			_playerMoveAnim->setPlayFrame(0, 4, false, true);
			_fishingLodAnim->setPlayFrame(14, 20, false, false);
		}
		else if (leftright < 0)
		{
			_playerMoveAnim->setPlayFrame(5, 9, false, true);
			_fishingLodAnim->setPlayFrame(21, 27, false, false);
		}
		else
		{
			_playerMoveAnim->setPlayFrame(15, 19, false, true);
			_fishingLodAnim->setPlayFrame(7, 13, false, false);
		}

		_fishingRange += 5.0f;
		if (_fishingRange > 200.0f) _fishingRange = 200.0f;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		if (GetPixel(_collisionMap->getMemDC(), point.x, point.y)
			== RGB(255, 0, 0)
			&& getDistance(_x, _y, point.x, point.y) < _fishingRange)
		{
			_fishingGreatZoneRC =
				RectMakeCenter(RND->getFromIntTo(_fishingBorderRC.left + 50, _fishingBorderRC.right - 50),
					CENTER_Y + 50,
					RND->getFromIntTo(30, 40),
					_fishingGreatZone->getHeight());
			_fishingPerfectZoneRC =
				RectMakeCenter(RND->getFromIntTo(_fishingGreatZoneRC.left + 10, _fishingGreatZoneRC.right - 10),
					CENTER_Y + 50,
					RND->getFromIntTo(5, 20),
					_fishingPerfectZone->getHeight());

			_isFishing = true;
			_fishingLodAnim->AniStart();
		}
		else
		{
			_isFishing = false;
		}

		_fishingRange = 0.0f;
	}
	if (_fishingLodAnim->getNowPlayIdx() == 4)
	{
		_fishingLodAnim->AniPause();
	}

}

void Player::Fishing()
{
	if (_fishingCursorRC.right >= _fishingBorderRC.right)
	{
		cursormovespeed = -cursormovespeed;
	}
	if (_fishingCursorRC.left <= _fishingBorderRC.left)
	{
		cursormovespeed = -cursormovespeed;
	}

	_fishingCursorRC.left += cursormovespeed;
	_fishingCursorRC.right += cursormovespeed;

	POINT cursorCenter = PointMake(_fishingCursorRC.left + (_fishingCursorRC.right - _fishingCursorRC.left) / 2,
		_fishingCursorRC.top + (_fishingCursorRC.bottom - _fishingCursorRC.top) / 2);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cursormovespeed = 0;
		
		if (PtInRect(&_fishingGreatZoneRC, cursorCenter))
		{

			if (PtInRect(&_fishingPerfectZoneRC, cursorCenter))
			{
				_isSuccessFishing = true;
			}
		}
		else
		{
			cout << "ºø³ª°¨" << endl;
		}

		_fishingLodAnim->AniResume();
		cursormovespeed = 3;
		_isFishing = false;
	}
}

void Player::getFishItem(bool successFishing, Inventory* inven, string index)
{
	if (successFishing)
	{
		inven->getItem(index);
	}

	_isSuccessFishing = false;
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

		float updown = object->getObjectList()[i]->getTilePos().y - _cy;
		float leftright = object->getObjectList()[i]->getTilePos().x - _cx;


		if (IntersectRect(&temp,
			&_playertoCameraRC,
			&object->getObjectList()[i]->getCollisionRC()))
		{
			cout << "¿ÀºêÁ§Æ® Ãæµ¹" << endl;

			cout << updown << ", " << leftright << endl;

			if (object->getObjectList()[i]->getType() > 1)
			{
				if (_playertoCameraRC.left <= object->getObjectList()[i]->getCollisionRC().right)
				{
					_x += _moveSpeed;
				}
				else if (_playertoCameraRC.right >= object->getObjectList()[i]->getCollisionRC().left)
				{
					_x -= _moveSpeed;
				}
				else if (_playertoCameraRC.top <= object->getObjectList()[i]->getCollisionRC().bottom)
				{
					_y += _moveSpeed;
				}
				else if (_playertoCameraRC.bottom >= object->getObjectList()[i]->getCollisionRC().top)
				{
					_y -= _moveSpeed;
				}

				
			}
		}
	}
}