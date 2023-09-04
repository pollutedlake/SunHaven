#include "Stdafx.h"
#include "Shadeclaw.h"
#include "Player_Temp.h"

HRESULT Shadeclaw::init(POINT position)
{
	_state = EShadeclawState::IDLE;
	_speed = 2.0f;

	return S_OK;
}

void Shadeclaw::release(void)
{

}

void Shadeclaw::update(void)
{
	switch (_state)
	{
	case EShadeclawState::IDLE:
		_imageName = "Shadeclow_Idle";

		break;

	case EShadeclawState::ATTACK:
		_imageName = "Shadeclow_Attack";

		break;

	case EShadeclawState::DIE:
		_imageName = "Shadeclow_Die";

		break;
	}

	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
}

void Shadeclaw::render(void)
{
	draw();
}

void Shadeclaw::move()
{
	
}

void Shadeclaw::attack()
{
	_state = EShadeclawState::ATTACK;

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
	animation();
}
