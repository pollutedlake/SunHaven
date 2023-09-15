#include "Stdafx.h"
#include "Dizzy.h"
#include "../../Player/Player.h"

HRESULT Dizzy::init(void)
{
	_state = EDizzyState::SLEEP;

	_wakeImg = IMAGEMANAGER->addFrameImage("DizzyWake", "Resources/Images/Boss/Dizzy/Dizzy_Wake.bmp",
		1218, 160, 7, 1, true, RGB(255, 0, 255));
	_idleImg = IMAGEMANAGER->addFrameImage("DizzyIdle", "Resources/Images/Boss/Dizzy/Dizzy_Idle.bmp",
		1392, 160, 8, 1, true, RGB(255, 0, 255));
	_spinImg = IMAGEMANAGER->addFrameImage("DizzySpin", "Resources/Images/Boss/Dizzy/Dizzy_Spin.bmp",
		4872, 320, 28, 2, true, RGB(255, 0, 255));
	_rangeImg = IMAGEMANAGER->addFrameImage("DizzyRange", "Resources/Images/Boss/Dizzy/Dizzy_Range.bmp",
		4176, 320, 24, 2, true, RGB(255, 0, 255));
	_deathImg = IMAGEMANAGER->addFrameImage("DizzyDeath", "Resources/Images/Boss/Dizzy/Dizzy_Death.bmp",
		1044, 320, 6, 2, true, RGB(255, 0, 255));

	_wakeAni = new Animation;
	_wakeAni->init(_wakeImg->getWidth(), _wakeImg->getHeight(), 174, 160);
	_wakeAni->setDefPlayFrame(false, true);
	_wakeAni->setFPS(12);

	_idleAni = new Animation;
	_idleAni->init(_idleImg->getWidth(), _idleImg->getHeight(), 174, 160);
	_idleAni->setDefPlayFrame(false, true);
	_idleAni->setFPS(12);

	_spinAni = new Animation;
	_spinAni->init(_spinImg->getWidth(), _spinImg->getHeight(), 174, 160);
	_spinAni->setDefPlayFrame(false, true);
	_spinAni->setFPS(12);

	_rangeAni = new Animation;
	_rangeAni->init(_rangeImg->getWidth(), _rangeImg->getHeight(), 174, 160);
	_rangeAni->setDefPlayFrame(false, true);
	_rangeAni->setFPS(12);

	_deathAni = new Animation;
	_deathAni->init(_deathImg->getWidth(), _deathImg->getHeight(), 174, 160);
	_deathAni->setDefPlayFrame(false, true);
	_deathAni->setFPS(12);

	_curImg = _wakeImg;
	_curAni = _wakeAni;
	//_curAni->AniStart();

	_x = CENTER_X + 200;
	_y = CENTER_Y + 200;

	_rcDizzy = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
	_rcSpinAtk = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());

	_collisionMap = IMAGEMANAGER->findImage("DizzyMapCollision");

	_hpBar = new ProgressBar;
	_hpBar->init("", "ProgressBarBGW", "ProgressBarW", CENTER_X + 15, CENTER_Y + 257, 92 * 4 + 25, 14);

	_hp = 5000.0f;
	_maxHp = 5000.0f;

	_isWake = false;
	_isDie = false;
	_isLeft = false;
	_worldTimeCount = GetTickCount();

	_rcColl[0] = RectMake(_rcDizzy.left, _rcDizzy.top - 3, 3, 3);
	_rcColl[1] = RectMake(_rcDizzy.right + 3, _rcDizzy.top, 3, 3);
	_rcColl[2] = RectMake(_rcDizzy.right - 3, _rcDizzy.top + 3, 3, 3);
	_rcColl[3] = RectMake(_rcDizzy.left - 3, _rcDizzy.top, 3, 3);

	_spinFromX = _spinFromY = 0.0f;
	_spinToX = _spinToY = 0.0f;
	_spinCount = 0;
	
	_meteor = new Meteor;
	_meteor->init("DizzyMeteor", 5, 1300.0f);

	_meteorFireX = 0.0f;
	_meteorFireY = 0.0f;

	_meteorIdx = 2;

	_meteorCount = 0;
	_fireCount = 0.0f;
	_turnCount = TIMEMANAGER->getWorldTime();
	_meteorFireCount = TIMEMANAGER->getWorldTime();
	_meteorTurnCount = 1.5f;

	_aftetMeteorCount = 0;

	_gem = new Gems;
	_gem->init(100, 1000.0f);

	_gemImg[128] = {};
	_rndGemImg = -1;

	_gemFireX = 0.0f;
	_gemFireY = 0.0f;

	_gemIdx = 4;

	_gemCount = 0;
	_fireCount2 = 0.0f;
	_turnCount2 = TIMEMANAGER->getWorldTime();
	_gemFireCount = TIMEMANAGER->getWorldTime();
	_gemTurnCount = 0.5f;

	_aftetGemCount = 0;

	_afterDeathTime = 0;
	_afterDeathWorldTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void Dizzy::release(void)
{
	_curAni->release();
	SAFE_DELETE(_curAni);

	_wakeAni->release();
	SAFE_DELETE(_wakeAni);

	_idleAni->release();
	SAFE_DELETE(_idleAni);

	_spinAni->release();
	SAFE_DELETE(_spinAni);

	_rangeAni->release();
	SAFE_DELETE(_rangeAni);

	_hpBar->release();
	SAFE_DELETE(_hpBar);

	_meteor->release();
	SAFE_DELETE(_meteor);

	_gem->release();
	SAFE_DELETE(_gem);

}

void Dizzy::update(void)
{
	_hpBar->update();
	_hpBar->setGauge(_hp, _maxHp);

	if (_hp <= 0)
	{
		_hp = 0;

		_state = EDizzyState::DEATH;

		_curAni->AniStop();
		_curImg = _deathImg;
		_curAni = _deathAni;

		if (!_isLeft)
		{
			_curAni->setPlayFrame(0, 5, false, false);
		}

		else
		{
			_curAni->setPlayFrame(6, 11, true, false);
		}

		_curAni->AniStart();
	}

	_meteor->update();
	_gem->update();

	_rcDizzy = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	if (_x < _player->getPlayerPosition().x && _state != EDizzyState::SPIN && 
		_state != EDizzyState::DEATH)
	{
		_isLeft = false;
	}

	if (_x >= _player->getPlayerPosition().x && _state != EDizzyState::SPIN &&
		_state != EDizzyState::DEATH)
	{
		_isLeft = true;
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_isWake = true;
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		_hp -= 1000;
	}

	switch (_state)
	{
	case EDizzyState::SLEEP:
		if (_isWake)
		{
			_state = EDizzyState::WAKE;

			_curAni->setPlayFrame(_curImg->getFrameX(), _curImg->getMaxFrameX(), false, false);
			_curAni->AniStart();
		}

		break;

	case EDizzyState::WAKE:
		if (_curAni->getNowPlayIdx() >= _curImg->getMaxFrameX())
		{
			_state = EDizzyState::IDLE;

			_curAni->AniStop();
			_curImg = _spinImg;
			_curAni = _spinAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(_curImg->getFrameX(), 11, false, true);
			}

			else
			{
				_curAni->setPlayFrame(44, 55, true, true);
			}

			_curAni->AniStart();
		}

		break;

	case EDizzyState::IDLE:
		if (_curAni->getNowPlayIdx() >= 11)
		{
			_state = EDizzyState::SPIN;

			_spinFromX = _x;
			_spinFromY = _y;
			_spinToX = _player->getPlayerPosition().x;
			_spinToY = _player->getPlayerPosition().y;

			_curAni->AniStop();

			if (!_isLeft)
			{
				_curAni->setPlayFrame(12, 16, false, true);
			}

			else
			{
				_curAni->setPlayFrame(39, 43, true, true);
			}

			_curAni->AniStart();
		}

		break;

	case EDizzyState::SPIN:
		spin();

		if (_isCollisionLeft || _isCollisionRight || _isCollisionTop || _isCollisionBottom)
		{
			if (_spinCount < 2)
			{
				_spinCount++;

				_state = EDizzyState::IDLE;
				
				_curAni->AniStop();
				_curImg = _spinImg;
				_curAni = _spinAni;

				if (!_isLeft)
				{
					_curAni->setPlayFrame(_curImg->getFrameX(), 11, false, true);
				}

				else
				{
					_curAni->setPlayFrame(44, 55, true, true);
				}

				_curAni->AniStart();
			}

			else
			{
				_spinCount = 0;
				_meteorIdx = 2;
				_state = EDizzyState::GROGGY;

				_curAni->AniStop();

				if (!_isLeft)
				{
					_curAni->setPlayFrame(17, 19, false, false);
					_curAni->AniPause();
					_curAni->setPlayFrame(20, 27, false, true);
				}

				else
				{
					_curAni->setPlayFrame(36, 38, true, false);
					_curAni->AniPause();
					_curAni->setPlayFrame(28, 35, true, true);
				}

				_curAni->AniResume();
			}
		}

		break;

	case EDizzyState::GROGGY:
		meteorFire();

		if (_meteorIdx == 0)
		{
			_aftetMeteorCount++;

			if (_aftetMeteorCount > 500)
			{
				_state = EDizzyState::RANGE;

				_curAni->AniStop();
				_curImg = _rangeImg;
				_curAni = _rangeAni;

				if (!_isLeft)
				{
					_curAni->setPlayFrame(0, 23, false, false);
				}

				else
				{
					_curAni->setPlayFrame(24, 47, true, false);
				}

				_curAni->AniStart();

				_aftetMeteorCount = 0;
				_gemCount = 0;
			}
		}

		break;

	case EDizzyState::RANGE:
		gemFire();

		if (_gemCount > 3)
		{
			_state = EDizzyState::IDLE;

			_curAni->AniStop();
			_curImg = _spinImg;
			_curAni = _spinAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 11, false, true);

			}

			else
			{
				_curAni->setPlayFrame(44, 55, true, true);

			}

			_curAni->AniStart();

			_spinCount = 0;
		}

		break;

	case EDizzyState::DEATH:
		if (_curAni->getNowPlayIdx() == 5 || _curAni->getNowPlayIdx() == 6)
		{
			//_curAni->AniStop();
			_afterDeathTime++;

			if (_afterDeathTime > 300)
			{
				cout << "죽었다" << endl;
				_isDie = true;
			}
		}

		break;
	}

	if (_collisionMap != nullptr)
	{
		for (int i = _rcDizzy.left + 4; i <= _rcDizzy.right - 4; i++)
		{
			COLORREF collisionT =
				GetPixel(_collisionMap->getMemDC(),
					i, _rcDizzy.top);
			COLORREF collisionB =
				GetPixel(_collisionMap->getMemDC(),
					i, _rcDizzy.bottom);

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

		for (int i = _rcDizzy.top + 4; i <= _rcDizzy.bottom - 4; i++)
		{
			COLORREF collisionL =
				GetPixel(_collisionMap->getMemDC(),
					_rcDizzy.left, i);

			COLORREF collisionR =
				GetPixel(_collisionMap->getMemDC(),
					_rcDizzy.right, i);

			_isCollisionLeft =
				collisionL == RGB(255, 0, 255) ? true : false;
			_isCollisionRight =
				collisionR == RGB(255, 0, 255) ? true : false;
		}
	}

}

void Dizzy::render(void)
{
	if (!_isDie)
	{
		draw();

		_hpBar->render();

		_meteor->render();
		_gem->render();

		char bossHpRate[128];

		sprintf_s(bossHpRate, "%d %s %d", static_cast<int>(_hp), "/", static_cast<int>(_maxHp));

		FONTMANAGER->textOut(getMemDC(), CENTER_X - 10, CENTER_Y + 230, "배달의민족 을지로체",
			20, 500, "디지", strlen("디지"), RGB(255, 255, 255));
		FONTMANAGER->textOut(getMemDC(), CENTER_X - 30, CENTER_Y + 250, "배달의민족 을지로체",
			15, 400, bossHpRate, strlen(bossHpRate), RGB(255, 255, 255));

		IMAGEMANAGER->render("DizzyHpBarBorder", getMemDC(), CENTER_X - 210, CENTER_Y + 223);
	}
}

void Dizzy::draw(void)
{
	//DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rcDizzy));
	
	_curImg->aniRender(getMemDC(), CAMERA->worldToCameraX(_x - _curImg->getFrameWidth() / 2), 
		CAMERA->worldToCameraY(_y - _curImg->getFrameHeight() / 2), _curAni);
}

void Dizzy::spin(void)
{
	float spinSpeed = 8.0f;
	
	if (_isCollisionLeft) _x += spinSpeed * 10;
	if (_isCollisionRight) _x -= spinSpeed * 10;
	if (_isCollisionTop) _y += spinSpeed * 10;
	if (_isCollisionBottom) _y -= spinSpeed * 10;

	_x += cosf(getAngle(_spinFromX, _spinFromY, _spinToX, _spinToY)) * spinSpeed;
	_y += -sinf(getAngle(_spinFromX, _spinFromY, _spinToX, _spinToY)) * spinSpeed;
}

void Dizzy::meteorFire(void)
{
	int meteorCountMax = RND->getFromIntTo(3, 5);

	_meteorFireX = RND->getFromFloatTo(0, 500.0f);
	_meteorFireY = RND->getFromFloatTo(0, 50.0f);

	if (_meteorCount < meteorCountMax && meteorCountFire())
	{
		_meteor->fire(_meteorFireX, _meteorFireY, getAngle(_meteorFireX, _meteorFireY, _meteorFireX + 10, _meteorFireY + 10), 10.0f);
		//_meteor->fire(0, 0, getAngle(0, 0, 1000, 600), 3.0f);

		_meteorCount++;
	}

	if (_meteorCount == meteorCountMax && turnCountFire() && _meteorIdx > 0)
	{
		_meteorCount = 0;

		_meteorIdx--;
	}
}

bool Dizzy::meteorCountFire(void)
{
	_fireCount = RND->getFromFloatTo(0.1f, 0.4f);

	if (_fireCount + _meteorFireCount <= TIMEMANAGER->getWorldTime())
	{
		_meteorFireCount = TIMEMANAGER->getWorldTime();
		_fireCount = RND->getFromFloatTo(0.1f, 0.3f);

		return true;
	}

	return false;
}

bool Dizzy::turnCountFire(void)
{
	if (_meteorTurnCount + _turnCount <= TIMEMANAGER->getWorldTime())
	{
		_turnCount = TIMEMANAGER->getWorldTime();

		_meteorTurnCount = 1.5f;

		return true;
	}

	return false;
}

void Dizzy::gemFire(void)
{
	int rndGemMax = RND->getFromIntTo(15, 25);

	if (gemCountFire())
	{
		for (int i = 0; i < rndGemMax; ++i)
		{
			_gem->fire(_x,
				_y,
				DEGREE_RADIAN(i * RND->getFromIntTo(15, 30)), RND->getFromFloatTo(5.0f, 6.0f));
		}

		_gemCount++;
	}
}

bool Dizzy::gemCountFire(void)
{
	_fireCount2 = 0.3f;

	if (_fireCount2 + _gemFireCount <= TIMEMANAGER->getWorldTime())
	{
		_gemFireCount = TIMEMANAGER->getWorldTime();
		_fireCount2 = 0.3f;

		return true;
	}

	return false;
}

bool Dizzy::turnCountFire2(void)
{
	if (_gemTurnCount + _turnCount2 <= TIMEMANAGER->getWorldTime())
	{
		_turnCount2 = TIMEMANAGER->getWorldTime();

		_gemTurnCount = 0.5f;

		return true;
	}

	return false;
}

bool Dizzy::afterDeathTime(void)
{
	if (_afterDeathTime + _afterDeathWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_afterDeathWorldTime = TIMEMANAGER->getWorldTime();

		_afterDeathTime = 5.5f;

		return true;
	}

	return false;
}
