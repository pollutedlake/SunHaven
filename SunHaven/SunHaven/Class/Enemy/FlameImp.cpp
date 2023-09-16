#include "Stdafx.h"
#include "FlameImp.h"

HRESULT FlameImp::init(POINT position)
{
	_x = position.x;
	_y = position.y;

	_worldTimeCount = GetTickCount();

	_state = EEnemyState::IDLE;

	_idleImg = IMAGEMANAGER->addFrameImage("FlameImp_Idle", "Resources/Images/Enemy/FlameImp/FlameImp_Idle.bmp",
		372 * 1.5, 100 * 1.5, 6, 2, true, RGB(255, 0, 255));
	_moveImg = IMAGEMANAGER->addFrameImage("FlameImp_Move", "Resources/Images/Enemy/FlameImp/FlameImp_Idle.bmp",
		372 * 1.5, 100 * 1.5, 6, 2, true, RGB(255, 0, 255));
	_atkImg = IMAGEMANAGER->addFrameImage("FlameImp_Attack", "Resources/Images/Enemy/FlameImp/FlameImp_Attack.bmp",
		744 * 1.5, 100 * 1.5, 12, 2, true, RGB(255, 0, 255));
	_deathImg = IMAGEMANAGER->addFrameImage("FlameImp_Die", "Resources/Images/Enemy/FlameImp/FlameImp_Die.bmp",
		806 * 1.5, 100 * 1.5, 13, 2, true, RGB(255, 0, 255));

	_idleAni = new Animation;
	_idleAni->init(_idleImg->getWidth(), _idleImg->getHeight(), 62 * 1.5, 50 * 1.5);
	_idleAni->setDefPlayFrame(false, true);
	_idleAni->setFPS(12);

	_moveAni = new Animation;
	_moveAni->init(_moveImg->getWidth(), _moveImg->getHeight(), 62 * 1.5, 50 * 1.5);
	_moveAni->setDefPlayFrame(false, true);
	_moveAni->setFPS(12);

	_atkAni = new Animation;
	_atkAni->init(_atkImg->getWidth(), _atkImg->getHeight(), 62 * 1.5, 50 * 1.5);
	_atkAni->setDefPlayFrame(false, true);
	_atkAni->setFPS(12);

	_deathAni = new Animation;
	_deathAni->init(_deathImg->getWidth(), _deathImg->getHeight(), 62 * 1.5, 50 * 1.5);
	_deathAni->setDefPlayFrame(false, true);
	_deathAni->setFPS(12);

	_curImg = _idleImg;
	_curAni = _idleAni;
	_curAni->setPlayFrame(0, 5, false, true);
	_curAni->AniStart();

	_speed = 1.0f;
	_targetOnSpeed = 1.5f;

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

	_fireball = new EnemyFireBall;
	_fireball->init("FlameImp_Fireball", 10, 1000.0f);
	_fireballSpeed = 3.0f;

	_patrolX = RND->getFromFloatTo(300, 700);
	_patrolY = RND->getFromFloatTo(200, 650);

	_detectRange = 250.0f;
	_attackRange = 200.0f;

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

void FlameImp::release(void)
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

	_fireball->release();
	SAFE_DELETE(_fireball);
}	

void FlameImp::update(void)
{

	_rc = RectMakeCenter(_x, _y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
	_curAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	if (_hp <= 0)
	{
		_hp = 0;

		_state = EEnemyState::DEATH;

		_curAni->AniStop();
		_curImg = _deathImg;
		_curAni = _deathAni;

		if (!_isLeft)
		{
			_curAni->setPlayFrame(0, 12, false, false);
		}

		else
		{
			_curAni->setPlayFrame(6, 11, true, false);
		}

		_curAni->AniStart();
	}

	_fireball->update();

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
				_curAni->setPlayFrame(0, 5, false, true);
			}

			else
			{
				_curAni->setPlayFrame(6, 11, true, true);
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
				_curAni->setPlayFrame(0, 5, false, true);
			}

			else
			{
				_curAni->setPlayFrame(6, 11, true, true);
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
				_curAni->setPlayFrame(0, 5, false, true);
			}

			else
			{
				_curAni->setPlayFrame(6, 11, true, true);
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
				_curAni->setPlayFrame(0, 5, false, true);
			}

			else
			{
				_curAni->setPlayFrame(6, 11, true, true);
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
				_curAni->setPlayFrame(0, 11, false, true);
			}

			else
			{
				_curAni->setPlayFrame(12, 23, true, true);
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
				_curAni->setPlayFrame(0, 5, false, false);
			}

			else
			{
				_curAni->setPlayFrame(6, 11, true, true);
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
		if (_curAni->getNowPlayIdx() == 9 || _curAni->getNowPlayIdx() == 14)
		{
			if (attackCoolDown())
			{
				attack();
			}
		}

		if (getDistance(_x, _y, _playerX, _playerY) > _attackRange)
		{
			_state = EEnemyState::TARGETON;

			_curAni->AniStop();
			_curImg = _moveImg;
			_curAni = _moveAni;

			if (!_isLeft)
			{
				_curAni->setPlayFrame(0, 5, false, true);
			}

			else
			{
				_curAni->setPlayFrame(6, 11, true, true);
			}

			_curAni->AniStart();
		}
		
		break;

	case EEnemyState::DEATH:


		break;
	}
}

void FlameImp::render(void)
{
	draw();
	_fireball->render();
}

void FlameImp::move(void)
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

void FlameImp::targetOn(void)
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

void FlameImp::attack(void)
{
	if (_x < _playerX)
	{
		_isLeft = false;
	}

	else
	{
		_isLeft = true;
	}

	_fireball->fire(_x, _y, getAngle(_atkFromX, _atkFromY, _atkToX, _atkToY), _fireballSpeed);
}

void FlameImp::draw(void)
{
	//DrawRectMake(getMemDC(), CAMERA->worldToCameraRect(_rc));

	_curImg->aniRender(getMemDC(), CAMERA->worldToCameraX(_x - _curImg->getFrameWidth() / 2),
		CAMERA->worldToCameraY(_y - _curImg->getFrameHeight() / 2), _curAni);
}

bool FlameImp::attackCoolDown(void)
{
	if (_afterAttackTime + _afterAttackWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_afterAttackWorldTime = TIMEMANAGER->getWorldTime();
		_afterAttackTime = 0.5f;

		return true;
	}

	return false;
}

void FlameImp::pixelCollision(void)
{
	if (_collisionMap != nullptr)
	{
		for (int i = _rc.left + 4; i <= _rc.right - 4; i++)
		{
			COLORREF collisionT =
				GetPixel(_collisionMap->getMemDC(),
					i, _rc.top);
			COLORREF collisionB =
				GetPixel(_collisionMap->getMemDC(),
					i, _rc.bottom);

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

		for (int i = _rc.top + 4; i <= _rc.bottom - 4; i++)
		{
			COLORREF collisionL =
				GetPixel(_collisionMap->getMemDC(),
					_rc.left, i);

			COLORREF collisionR =
				GetPixel(_collisionMap->getMemDC(),
					_rc.right, i);

			_isCollisionLeft =
				collisionL == RGB(255, 0, 255) ? true : false;
			_isCollisionRight =
				collisionR == RGB(255, 0, 255) ? true : false;
		}
	}
}
