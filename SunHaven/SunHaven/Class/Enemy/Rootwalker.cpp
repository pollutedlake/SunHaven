#include "Stdafx.h"
#include "Rootwalker.h"

HRESULT Rootwalker::init(POINT position)
{
	_x = position.x;
	_y = position.y;

	_worldTimeCount = GetTickCount();

	_state = EEnemyState::IDLE;

	_idleImg = IMAGEMANAGER->addFrameImage("Rootwalker_Idle", "Resources/Images/Enemy/Rootwalker/Rootwalker_Idle.bmp",
		135 * 2, 84 * 2, 3, 2, true, RGB(255, 0, 255));
	_moveImg = IMAGEMANAGER->addFrameImage("Rootwalker_Move", "Resources/Images/Enemy/Rootwalker/Rootwalker_Move.bmp",
		135 * 2, 84 * 2, 3, 2, true, RGB(255, 0, 255));
	_atkImg = IMAGEMANAGER->addFrameImage("Rootwalker_Attack", "Resources/Images/Enemy/Rootwalker/Rootwalker_Attack.bmp",
		135 * 2, 84 * 2, 3, 2, true, RGB(255, 0, 255));
	_deathImg = IMAGEMANAGER->addFrameImage("Rootwalker_Death", "Resources/Images/Enemy/Rootwalker/Rootwalker_Death.bmp",
		180 * 2, 84 * 2, 4, 2, true, RGB(255, 0, 255));

	_idleAni = new Animation;
	_idleAni->init(_idleImg->getWidth(), _idleImg->getHeight(), 45 * 2, 42 * 2);
	_idleAni->setDefPlayFrame(false, true);
	_idleAni->setFPS(12);

	_moveAni = new Animation;
	_moveAni->init(_moveImg->getWidth(), _moveImg->getHeight(), 45 * 2, 42 * 2);
	_moveAni->setDefPlayFrame(false, true);
	_moveAni->setFPS(12);

	_atkAni = new Animation;
	_atkAni->init(_atkImg->getWidth(), _atkImg->getHeight(), 45 * 2, 42 * 2);
	_atkAni->setDefPlayFrame(false, true);
	_atkAni->setFPS(12);

	_deathAni = new Animation;
	_deathAni->init(_deathImg->getWidth(), _deathImg->getHeight(), 45 * 2, 42 * 2);
	_deathAni->setDefPlayFrame(false, true);
	_deathAni->setFPS(12);

	_curImg = _idleImg;
	_curAni = _idleAni;
	_curAni->setPlayFrame(0, 3, false, true);
	_curAni->AniStart();

	_speed = 0.5f;
	_targetOnSpeed = 1.5f;

	_rc = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());

	_collisionMap = IMAGEMANAGER->findImage("DynusMapCollision");

	_hpBar = new ProgressBar;
	//_hpBar->init("", "ProgressBarBGW", "ProgressBarW", _x, _y - 100, 92 * 4 + 25, 14);

	_hp = 100.0f;
	_maxHp = 100.0f;

	_isLeft = false;

	_playerX = _playerY = 0.0f;

	_patrolX = RND->getFromFloatTo(300, 700);
	_patrolY = RND->getFromFloatTo(200, 650);

	_detectRange = 200.0f;
	_attackRange = 50.0f;

	_waitTime = 5.0f;
	_waitCount = 0.0f;
	_patrolPoints = deque<pair<float, float>>();
	_patrolPoints.push_back(make_pair(_patrolX, _patrolY));

	if (!_patrolPoints.empty())
	{
		_nextPoints = _patrolPoints.front();
		_patrolPoints.pop_front();
	}

	_afterAttackTime = 0.5f;
	_afterAttackWorldTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void Rootwalker::release(void)
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

void Rootwalker::update(void)
{
	_rc = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	pixelCollision();

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
				_curAni->setPlayFrame(0, 2, false, true);
			}

			else
			{
				_curAni->setPlayFrame(3, 5, true, true);
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
				_curAni->setPlayFrame(0, 2, false, true);
			}

			else
			{
				_curAni->setPlayFrame(3, 5, true, true);
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

			_curAni->AniStop();
			_curImg = _idleImg;
			_curAni = _idleAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 2, false, true);

			}

			else
			{
				_curAni->setPlayFrame(3, 5, true, true);

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
				_curAni->setPlayFrame(0, 2, false, true);

			}

			else
			{
				_curAni->setPlayFrame(3, 5, true, true);

			}

			_curAni->AniStart();
		}

		break;

	case EEnemyState::TARGETON:
		targetOn();

		if (getDistance(_x, _y, _playerX, _playerY) <= _attackRange)
		{
			_state = EEnemyState::ATTACK;

			_curAni->AniStop();
			_curImg = _atkImg;
			_curAni = _atkAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 2, false, false);

				if ((_curAni->getNowPlayIdx() == 1))
				{
					_rcAttack = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
				}

				else
				{
					_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
				}
			}

			else
			{
				_curAni->setPlayFrame(3, 5, true, false);

				if ((_curAni->getNowPlayIdx() == 4))
				{
					_rcAttack = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
				}

				else
				{
					_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
				}
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
				_curAni->setPlayFrame(0, 2, false, true);

			}

			else
			{
				_curAni->setPlayFrame(3, 5, true, true);

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

		if (attackCoolDown())
		{
			_state = EEnemyState::TARGETON;

			_curAni->AniStop();
			_curImg = _moveImg;
			_curAni = _moveAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 2, false, true);
			}

			else
			{
				_curAni->setPlayFrame(3, 5, true, true);
			}

			_curAni->AniStart();
		}

		break;

	case EEnemyState::DEATH:


		break;
	}
}

void Rootwalker::render(void)
{
	draw();
}

void Rootwalker::move(void)
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

void Rootwalker::targetOn(void)
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

void Rootwalker::attack(void)
{
	DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rcAttack));

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
		if ((_curAni->getNowPlayIdx() == 1))
		{
			_rcAttack = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
		}

		else
		{
			_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
		}
	}

	else
	{
		if ((_curAni->getNowPlayIdx() == 4))
		{
			_rcAttack = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
		}

		else
		{
			_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
		}
	}
}

void Rootwalker::draw(void)
{
	_curImg->aniRender(getMemDC(), CAMERA->worldToCameraX(_x - _curImg->getFrameWidth() / 2),
		CAMERA->worldToCameraY(_y - _curImg->getFrameHeight() / 2), _curAni);
}

bool Rootwalker::attackCoolDown(void)
{
	if (_afterAttackTime + _afterAttackWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_afterAttackWorldTime = TIMEMANAGER->getWorldTime();
		_afterAttackTime = 0.5f;

		return true;
	}

	return false;
}
