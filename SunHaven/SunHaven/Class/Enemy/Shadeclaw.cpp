#include "Stdafx.h"
#include "Shadeclaw.h"

HRESULT Shadeclaw::init(POINT position)
{
	/*_x = position.x;
	_y = position.y;

	_worldTimeCount = GetTickCount();

	_state = EEnemyState::MOVE;
	_speed = 1.0f;

	_imageName = "Shadeclow_Idle";
	_image = IMAGEMANAGER->findImage(_imageName);

	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());

	_isLeft = false;

	_playerX = _playerY = 0.0f;

	_patrolX = RND->getFromFloatTo(300, 700);
	_patrolY = RND->getFromFloatTo(200, 650);

	_waitTime = 5.0f;
	_waitCount = 0.0f;
	_patrolPoints = deque<pair<float, float>>();
	_patrolPoints.push_back(make_pair(_patrolX, _patrolY));

	if (!_patrolPoints.empty())
	{
		_nextPoints = _patrolPoints.front();
		_patrolPoints.pop_front();
	}*/

	return S_OK;
}

void Shadeclaw::release(void)
{

}

void Shadeclaw::update(void)
{
	//switch (_state)
	//{
	//case EEnemyState::IDLE:
	//	_imageName = "Shadeclow_Idle";

	//	_waitCount++;

	//	if (_waitCount > 300)
	//	{
	//		_patrolX = RND->getFromFloatTo(300, 700);
	//		_patrolY = RND->getFromFloatTo(200, 650);

	//		_patrolPoints.push_back(make_pair(_patrolX, _patrolY));
	//		if (!_patrolPoints.empty())
	//		{
	//			//_patrolPoints.push_back(_nextPoints);

	//			_nextPoints = _patrolPoints.front();
	//			_patrolPoints.pop_front();
	//			_state = EEnemyState::MOVE;
	//		}
	//	}

	//	break;

	//case EEnemyState::MOVE:
	//	_imageName = "Shadeclow_Idle";

	//	move();

	//	if (getDistance(_x, _y, _nextPoints.first, _nextPoints.second) <= 10.0f)
	//	{
	//		_worldTimeCount = 0.0f;

	//		_waitCount = 0.0f;
	//		_state = EEnemyState::IDLE;
	//	}

	//	break;

	//case EEnemyState::TARGETON:
	//	_imageName = "Shadeclow_Idle";
	//
	//	targetOn();

	//	break;

	//case EEnemyState::ATTACK:
	//	_imageName = "Shadeclow_Attack";



	//	attack();

	//	break;

	//case EEnemyState::DEATH:
	//	_imageName = "Shadeclow_Die";
	//	

	//	break;
	//}

	/*_image = IMAGEMANAGER->findImage(_imageName);
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());

	
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
	}*/
}

void Shadeclaw::render(void)
{
	draw();
}

void Shadeclaw::move()
{

	if (_x < _patrolX)
	{
		_isLeft = false; // 坷弗率
	}

	else
	{
		_isLeft = true; // 哭率
	}

	_x += cosf(getAngle(_x, _y, _nextPoints.first, _nextPoints.second)) * _speed;
	_y += -sinf(getAngle(_x, _y, _nextPoints.first, _nextPoints.second)) * _speed;
}

void Shadeclaw::targetOn(void)
{

	//if ((_rc.left + _rc.right) / 2 < _playerX)
	//{
	//	_isLeft = false; // 坷弗率
	//}

	//else
	//{
	//	_isLeft = true; // 哭率
	//}

	_x += cosf(getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
		_playerX, _playerY)) * _speed;

	_y += -sinf(getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
		_playerX, _playerY)) * _speed;
}

void Shadeclaw::attack()
{

	//if (_x < _playerX)
	//{
	//	_isLeft = false; // 坷弗率
	//}
	//else
	//{
	//	_isLeft = true; // 哭率
	//}

	//if (!_isLeft)
	//{
	//	if (_currentFrameX == 3 || _currentFrameX == 4 || _currentFrameX == 7 || _currentFrameX == 8)
	//	{
	//		_rcAttack = RectMakeCenter(_x + 50, _y + 30, 80, 80);
	//	}

	//	else
	//	{
	//		_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
	//	}
	//}

	//else
	//{
	//	if (_currentFrameX == 2 || _currentFrameX == 3 || _currentFrameX == 6 || _currentFrameX == 7)
	//	{
	//		_rcAttack = RectMakeCenter(_x + 40, _y + 30, 80, 80);
	//	}

	//	else
	//	{
	//		_rcAttack = RectMakeCenter(-10000, 0, 0, 0);
	//	}
	//}
}

void Shadeclaw::draw()
{
	/*DrawRectMake(getMemDC(), _rcAttack);
	_image->frameRender(getMemDC(), _x, _y);*/
}
