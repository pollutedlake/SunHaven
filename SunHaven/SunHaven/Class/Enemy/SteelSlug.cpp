#include "Stdafx.h"
#include "SteelSlug.h"

HRESULT SteelSlug::init(POINT position)
{
	_x = position.x;
	_y = position.y;

	_worldTimeCount = GetTickCount();

	_state = EEnemyState::IDLE;

	_idleImg = IMAGEMANAGER->addFrameImage("SteelSlug_Idle", "Resources/Images/Enemy/SteelSlug/SteelSlug_Idle.bmp",
		144 * 1.5, 56 * 1.5, 4, 2, true, RGB(255, 0, 255));
	_moveImg = IMAGEMANAGER->addFrameImage("SteelSlug_Move", "Resources/Images/Enemy/SteelSlug/SteelSlug_Move.bmp",
		144 * 1.5, 56 * 1.5, 4, 2, true, RGB(255, 0, 255));
	_atkImg = IMAGEMANAGER->addFrameImage("SteelSlug_Attack", "Resources/Images/Enemy/SteelSlug/SteelSlug_Attack.bmp",
		576 * 1.5, 56 * 1.5, 16, 2, true, RGB(255, 0, 255));
	_deathImg = IMAGEMANAGER->addFrameImage("SteelSlug_Die", "Resources/Images/Enemy/SteelSlug/SteelSlug_Die.bmp",
		324 * 1.5, 56 * 1.5, 9, 2, true, RGB(255, 0, 255));

	_idleAni = new Animation;
	_idleAni->init(_idleImg->getWidth(), _idleImg->getHeight(), 36 * 1.5, 28 * 1.5);
	_idleAni->setDefPlayFrame(false, true);
	_idleAni->setFPS(12);

	_moveAni = new Animation;
	_moveAni->init(_moveImg->getWidth(), _moveImg->getHeight(), 36 * 1.5, 28 * 1.5);
	_moveAni->setDefPlayFrame(false, true);
	_moveAni->setFPS(12);

	_atkAni = new Animation;
	_atkAni->init(_atkImg->getWidth(), _atkImg->getHeight(), 36 * 1.5, 28 * 1.5);
	_atkAni->setDefPlayFrame(false, true);
	_atkAni->setFPS(12);

	_deathAni = new Animation;
	_deathAni->init(_deathImg->getWidth(), _deathImg->getHeight(), 36 * 1.5, 28 * 1.5);
	_deathAni->setDefPlayFrame(false, true);
	_deathAni->setFPS(12);

	_curImg = _idleImg;
	_curAni = _idleAni;
	_curAni->setPlayFrame(0, 3, false, true);
	_curAni->AniStart();

	_speed = 0.5f;
	_targetOnSpeed = 1.5f;
	_atkSpeed = 4.0f;

	_rc = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());

	_collisionMap = IMAGEMANAGER->findImage("MineMapCollision");

	_hpBar = new ProgressBar;
	//_hpBar->init("", "ProgressBarBGW", "ProgressBarW", _x, _y - 100, 92 * 4 + 25, 14);

	_hp = 100.0f;
	_maxHp = 100.0f;

	_isLeft = false;

	_atkFromX = _atkFromY = 0.0f;
	_atkToX = _atkToY = 0.0f;
	_playerX = _playerY = 0.0f;

	
	_patrolX = RND->getFromFloatTo(600, 1500);
	_patrolY = RND->getFromFloatTo(1200, 2000);

	_detectRange = 200.0f;
	_attackRange = 60.0f;

	_waitTime = 5.0f;
	_waitCount = 0.0f;
	_patrolPoints = deque<pair<float, float>>();
	_patrolPoints.push_back(make_pair(_patrolX, _patrolY));

	if (!_patrolPoints.empty())
	{
		_nextPoints = _patrolPoints.front();
		_patrolPoints.pop_front();
	}

	_afterAttackTime = 1.5f;
	_afterAttackWorldTime = TIMEMANAGER->getWorldTime();

	_isDie = false;
	
	return S_OK;
}

void SteelSlug::release(void)
{
	_curAni->release();
	SAFE_DELETE(_curAni);

	_idleAni->release();
	SAFE_DELETE(_idleAni);

	_moveAni->release();
	SAFE_DELETE(_moveAni);

	_deathAni->release();
	SAFE_DELETE(_deathAni);

	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void SteelSlug::update(void)
{

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_hp -= 10;
	}
	if (_hp <= 0)
	{
		_hp = 0;

		_state = EEnemyState::DEATH;

		_curAni->AniStop();
		_curImg = _deathImg;
		_curAni = _deathAni;

		if (!_isLeft)
		{
			_curAni->setPlayFrame(0, 8, false, false);
		}

		else
		{
			_curAni->setPlayFrame(9, 17, true, false);
		}

		_curAni->AniStart();
	}

	else
	{
		_rc = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
		_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

		pixelCollision();
	}

	switch (_state)
	{
	case EEnemyState::IDLE:
		if (isWait())
		{
			_state = EEnemyState::PATROL;

			_curAni->AniStop();
			_curImg = _moveImg;
			_curAni = _moveAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 3, false, true);
			}

			else
			{
				_curAni->setPlayFrame(4, 7, true, true);
			}

			_curAni->AniStart();
		}

		if (getDistance(_x, _y, _playerX, _playerY) > _attackRange &&
			getDistance(_x, _y, _playerX, _playerY) <= _detectRange)
		{
			_state = EEnemyState::TARGETON;

			_curAni->AniStop();
			_curImg = _moveImg;
			_curAni = _moveAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 3, false, true);
			}

			else
			{
				_curAni->setPlayFrame(4, 7, true, true);
			}

			_curAni->AniStart();
		}

		break;

	case EEnemyState::PATROL:
		move();

		if (getDistance(_x, _y, _nextPoints.first, _nextPoints.second) <= 10.0f ||
			_isCollisionLeft || _isCollisionRight || _isCollisionTop || _isCollisionBottom)
		{
			_state = EEnemyState::IDLE;
			
			_patrolPoints.push_back(make_pair(_patrolX, _patrolY));

			if (!_patrolPoints.empty())
			{
				_nextPoints = _patrolPoints.front();
				_patrolPoints.pop_front();
			}

			_curAni->AniStop();
			_curImg = _idleImg;
			_curAni = _idleAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 3, false, true);

			}

			else
			{
				_curAni->setPlayFrame(4, 7, true, true);

			}

			_curAni->AniStart();
		}

		if (getDistance(_x, _y, _playerX, _playerY) > _attackRange &&
			getDistance(_x, _y, _playerX, _playerY) <= _detectRange)
		{
			_state = EEnemyState::TARGETON;

			_curAni->AniStop();
			_curImg = _moveImg;
			_curAni = _moveAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 3, false, true);

			}

			else
			{
				_curAni->setPlayFrame(4, 7, true, true);

			}

			_curAni->AniStart();
		}

		break;

	case EEnemyState::TARGETON:
		targetOn();

		if (getDistance(_x, _y, _playerX, _playerY) <= _attackRange)
		{
			_state = EEnemyState::ATTACK;

			_atkFromX = _x;
			_atkFromY = _y;
			_atkToX = _playerX;
			_atkToY = _playerY;

			_curAni->AniStop();
			_curImg = _atkImg;
			_curAni = _atkAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 15, false, true);
			}

			else
			{
				_curAni->setPlayFrame(16, 31, true, true);
			}

			_curAni->AniStart();
		}

		if (getDistance(_x, _y, _playerX, _playerY) > _detectRange)
		{
			_state = EEnemyState::IDLE;

			_curAni->AniStop();
			_curImg = _idleImg;
			_curAni = _idleAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 3, false, true);

			}

			else
			{
				_curAni->setPlayFrame(4, 7, true, true);

			}

			_curAni->AniStart();
		}

		if (_isCollisionLeft || _isCollisionRight || _isCollisionTop || _isCollisionBottom)
		{
			_x -= cosf(getAngle(_x, _y, _playerX, _playerY)) * _targetOnSpeed;
			_y -= -sinf(getAngle(_x, _y, _playerX, _playerY)) * _targetOnSpeed;
		}

		break;

	case EEnemyState::ATTACK:
		attack();

		if (_curAni->getNowPlayIdx() == 15 || _curAni->getNowPlayIdx() == 16)
		{
			_curAni->AniPause();

			if (attackCoolDown())
			{
				_state = EEnemyState::TARGETON;

				_curAni->AniStop();
				_curImg = _moveImg;
				_curAni = _moveAni;

				if (!_isLeft)
				{
					_curAni->setPlayFrame(0, 3, false, true);
				}

				else
				{
					_curAni->setPlayFrame(4, 7, true, true);
				}

				_curAni->AniStart();
			}
		}

		break;

	case EEnemyState::DEATH:
		if (_curAni->getNowPlayIdx() == 8 || _curAni->getNowPlayIdx() == 9)
		{
			// SD: Á×À½
			
			_isDie = true;
		}

		break;
	}

	if (_isDamaged)
	{
		_invincibilityTime += TIMEMANAGER->getElapsedTime();

		if (_invincibilityTime > 0.4f)
		{
			_isDamaged = false;
			_invincibilityTime = 0.0f;
		}
	}
}

void SteelSlug::render(void)
{
	if (!_isDie)
	{
		draw();
	}
}

void SteelSlug::move(void)
{
	if (_x < _nextPoints.first)
	{
		_isLeft = false;
	}

	else
	{
		_isLeft = true;
	}

	_x += cosf(getAngle(_x, _y, _nextPoints.first, _nextPoints.second)) * _speed;
	_y += -sinf(getAngle(_x, _y, _nextPoints.first, _nextPoints.second)) * _speed;
}

void SteelSlug::targetOn(void)
{
	if (_x < _playerX)
	{
		_isLeft = false;
	}

	else
	{
		_isLeft = true;
	}

	_x += cosf(getAngle(_x, _y, _playerX, _playerY)) * _targetOnSpeed;
	_y += -sinf(getAngle(_x, _y, _playerX, _playerY)) * _targetOnSpeed;
}

void SteelSlug::attack(void)
{
	if (_x < _playerX)
	{
		_isLeft = false;
	}

	else
	{
		_isLeft = true;
	}

	if (!_isLeft)
	{
		if (_curAni->getNowPlayIdx() >= 8 && _curAni->getNowPlayIdx() < 15)
		{
			_x += cosf(getAngle(_atkFromX, _atkFromY, _atkToX, _atkToY)) * _atkSpeed;
			_y += -sinf(getAngle(_atkFromX, _atkFromY, _atkToX, _atkToY)) * _atkSpeed;

			_rcAttack = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
		}

		else
		{
			_rcAttack = RectMakeCenter(0, 0, 0, 0);
		}
	}

	else
	{
		if (_curAni->getNowPlayIdx() > 16 && _curAni->getNowPlayIdx() <= 23)
		{
			_x += cosf(getAngle(_atkFromX, _atkFromY, _atkToX, _atkToY)) * _atkSpeed;
			_y += -sinf(getAngle(_atkFromX, _atkFromY, _atkToX, _atkToY)) * _atkSpeed;

			_rcAttack = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
		}

		else
		{
			_rcAttack = RectMakeCenter(0, 0, 0, 0);
		}
	}

	if (_isCollisionLeft || _isCollisionRight || _isCollisionTop || _isCollisionBottom)
	{
		_x -= cosf(getAngle(_atkFromX, _atkFromY, _atkToX, _atkToY)) * _atkSpeed;
		_y -= -sinf(getAngle(_atkFromX, _atkFromY, _atkToX, _atkToY)) * _atkSpeed;
	}
}

void SteelSlug::draw(void)
{
	_curImg->aniRender(getMemDC(), CAMERA->worldToCameraX(_x - _curImg->getFrameWidth() / 2), 
		CAMERA->worldToCameraY(_y - _curImg->getFrameHeight() / 2), _curAni);
}

bool SteelSlug::attackCoolDown(void)
{
	if (_afterAttackTime + _afterAttackWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_afterAttackWorldTime = TIMEMANAGER->getWorldTime();
		_afterAttackTime = 1.5f;

		return true;
	}

	return false;
}
