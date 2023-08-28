#include "stdafx.h"
#include "Enemy.h"
#include "Bullets.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
					_currentFrameX(0),
					_currentFrameY(0),
					_x(0.0f),
					_y(0.0f),
					_worldTimeCount(0.0f),
					_rndTimeCount(0.0f),
					_rndFireCount(0.0f),
					_bulletFireCount(0.0f)
{
}

HRESULT Enemy::init(void)
{
	// Do nothing !

	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
	_x = position.x;
	_y = position.y;

	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);

	_image = IMAGEMANAGER->findImage(imageName);;
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

// X: 적마다 움직임이 다르다 -> 상속을 전재한 클래스인데.. -> 자식 구현
void Enemy::move(void)
{

}

void Enemy::draw(void)
{
	_image->frameRender(getMemDC(), _x, _y,
		_currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_currentFrameX++;

		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
}

bool Enemy::bulletCountFire(void)
{
	if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);

		return true;
	}

	return false;
}
