#include "Stdafx.h"
#include "Shadeclaw.h"

HRESULT Shadeclaw::init(POINT position)
{
	_x = position.x;
	_y = position.y;

	_state = EEnemyState::MOVE;
	_speed = 1.0f;

	_imageName = "Shadeclow_Idle";
	_image = IMAGEMANAGER->findImage(_imageName);

	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());

	_isLeft = false;

	_playerX = _playerY = 0.0f;

	_waitTime = 5.0f;
	_patrolPoints = deque<pair<float, float>>();
	_patrolPoints.push_back(make_pair(RND->getFromFloatTo(300, 700), RND->getFromFloatTo(200, 650)));

	if (!_patrolPoints.empty())
	{
		_nextPoints = _patrolPoints.front();
		_patrolPoints.pop_front();
	}

	return S_OK;
}

void Shadeclaw::release(void)
{

}

void Shadeclaw::update(void)
{
	switch (_state)
	{
	case EEnemyState::IDLE:
		_imageName = "Shadeclow_Idle";

		cout << _worldTimeCount << endl;

		if (_worldTimeCount >= _waitTime)
		{
			_patrolPoints.push_back(make_pair(RND->getFromFloatTo(300, 700), RND->getFromFloatTo(200, 650)));
			if (!_patrolPoints.empty())
			{
				//_patrolPoints.push_back(_nextPoints);

				_nextPoints = _patrolPoints.front();
				_patrolPoints.pop_front();
				_state = EEnemyState::MOVE;
			}
		}

		break;

	case EEnemyState::MOVE:
		_imageName = "Shadeclow_Idle";

		move();

		// 다음 Patrol 위치에 도착하면 대기 상태로 전환
		if (getDistance(_x, _y, _nextPoints.first, _nextPoints.second) <= 10.0f)
		{
			
			_worldTimeCount = 0.0f;

			
			_state = EEnemyState::IDLE;
		}

		break;

	case EEnemyState::TARGETON:
		_imageName = "Shadeclow_Idle";

		targetOn();

		break;

	case EEnemyState::ATTACK:
		_imageName = "Shadeclow_Attack";



		attack();

		break;

	case EEnemyState::DIE:
		_imageName = "Shadeclow_Die";
		

		break;
	}
	_image = IMAGEMANAGER->findImage(_imageName);
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());

	if (_playerX < _x) {
		_isLeft = true; // 왼쪽 방향
	}
	else {
		_isLeft = false; // 오른쪽 방향
	}

	cout << _x << endl;
	cout << _playerY << endl;
	
	if (getDistance(_x, _y, _playerX, _playerY) > 200)
	{
		_state = EEnemyState::MOVE;
	}

	else if (getDistance(_x, _y, _playerX, _playerY) > 50 &&
		getDistance(_x, _y, _playerX, _playerY) <= 200)
	{
		_state = EEnemyState::TARGETON;
	}

	else if (getDistance(_x, _y, _playerX, _playerY) <= 50)
	{
		_state = EEnemyState::ATTACK;
	}
}

void Shadeclaw::render(void)
{
	draw();
	animation();
}

void Shadeclaw::move()
{
	cout << "Move To PatrolPos" << endl;

		_x += cosf(getAngle(_x, _y, _nextPoints.first, _nextPoints.second)) * _speed;
		_y += -sinf(getAngle(_x, _y, _nextPoints.first, _nextPoints.second)) * _speed;
}

void Shadeclaw::targetOn(void)
{
	cout << "Move To Target" << endl;

	_x += cosf(getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
		_playerX, _playerY)) * _speed;

	_y += -sinf(getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
		_playerX, _playerY)) * _speed;
}

void Shadeclaw::attack()
{
	cout << "Attack To Target" << endl;

	if (!_isLeft)
	{
		if (_currentFrameX == 3 || _currentFrameX == 4 || _currentFrameX == 7 || _currentFrameX == 8)
		{
			_rcAttack = RectMakeCenter(_x + 50, _y + 30, 80, 80);
		}

		else
		{
			_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
		}
	}

	/*else
	{
		if (_currentFrameX == 2 || _currentFrameX == 3 || _currentFrameX == 6 || _currentFrameX == 7)
		{
			_rcAttack = RectMakeCenter(_x + 50, _y + 30, 80, 80);
		}

		else
		{
			_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
		}
	}*/
}

void Shadeclaw::animation()
{
	if (!_isLeft)	// 오른쪽
	{
		_image->setFrameY(0);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;

			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameX = 0;

				_state = EEnemyState::IDLE;
			}
		}
	}

	else	// 왼쪽
	{
		_image->setFrameY(1);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX--;

			if (0 > _currentFrameX)
			{
				_currentFrameX = _image->getMaxFrameX();

				_state = EEnemyState::IDLE;
			}
		}
	}
}

void Shadeclaw::draw()
{
	DrawRectMake(getMemDC(), _rcAttack);
	_image->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}
