#include "Stdafx.h"
#include "Shadeclaw.h"
#include "Player_Temp.h"

HRESULT Shadeclaw::init(POINT position)
{
	_x = position.x;
	_y = position.y;

	_state = EEnemyState::IDLE;
	_speed = 2.0f;

	_imageName = "Shadeclow_Idle";
	_image = IMAGEMANAGER->findImage(_imageName);

	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());



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

		break;

	case EEnemyState::MOVE:
		_imageName = "Shadeclow_Idle";

		break;

	case EEnemyState::ATTACK:
		_imageName = "Shadeclow_Attack";

		break;

	case EEnemyState::DIE:
		_imageName = "Shadeclow_Die";

		break;
	}

	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());

	move();
}

void Shadeclaw::render(void)
{
	draw();
	animation();
}

void Shadeclaw::move()
{
	//cout << "Move To Target" << endl;

	if (getDistance(_x, _y, _playerX, _playerY) > 50 &&
		getDistance(_x, _y, _playerX, _playerY) < 200)
	{
		cout << "Move To Target" << endl;

		_x += cosf(getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
			_playerX, _playerY)) * 2.0f;

		_y += -sinf(getAngle((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2,
			_playerX, _playerY)) * 2.0f;
	}

	else if (getDistance(_x, _y, _playerX, _playerY) <= 50)
	{
		cout << "Attack To Target" << endl;

		attack();
	}
}

void Shadeclaw::attack()
{
	_state = EEnemyState::ATTACK;

	//_player
}

void Shadeclaw::animation()
{
	if (!_isLeft)	// ¿À¸¥ÂÊ
	{
		_image->setFrameY(0);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX++;

			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameX = 0;

				//_state = EShadeclawState::IDLE;
			}
		}
	}

	else	// ¿ÞÂÊ
	{
		_image->setFrameY(1);

		if (130 + _worldTimeCount <= GetTickCount())
		{
			_worldTimeCount = GetTickCount();
			_currentFrameX--;

			if (0 > _currentFrameX)
			{
				_currentFrameX = _image->getMaxFrameX();

				//_state = EShadeclawState::IDLE;
			}
		}
	}
}

void Shadeclaw::draw()
{
	_image->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}
