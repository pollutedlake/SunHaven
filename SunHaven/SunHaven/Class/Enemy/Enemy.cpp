#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
					_imageName(""),
					_currentFrameX(0),
					_currentFrameY(0),
					_x(0.0f),
					_y(0.0f),
					_worldTimeCount(0.0f),
					_timeCount(0.0f),
					_fireCount(0.0f),
					_bulletFireCount(0.0f),
					_isLeft(false)
{
}

HRESULT Enemy::init(void)
{
	// Do nothing !

	return S_OK;
}

HRESULT Enemy::init(POINT position)
{
	_x = position.x;
	_y = position.y;

	_worldTimeCount = GetTickCount();
	_timeCount = 100;

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_fireCount = 2.5f;

	_imageName = "Shadeclow_Idle";
	_image = IMAGEMANAGER->findImage(_imageName);
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void Enemy::release(void)
{
	// Do nothing !
}

void Enemy::update(void)
{
	move();
	//collisionCheck();
}

void Enemy::render(void)
{
	draw();
	animation();
}

void Enemy::move(void)
{

}

void Enemy::attack(void)
{
}

void Enemy::draw(void)
{
	if (KEYMANAGER->isToggleKey('H'))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

		DrawRectMake(getMemDC(), _rc);

		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myBrush);
	}

	_image->frameRender(getMemDC(), _x, _y,
		_currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
{
	/*if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_currentFrameX++;

		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}*/
}

bool Enemy::bulletCountFire(void)
{
	if (_fireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireCount = 2.5f;

		return true;
	}

	return false;
}
