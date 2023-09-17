#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
					_rcAttack(RectMake(0, 0, 0, 0)),
					_hp(0.0f),
					_maxHp(0.0f),
					_detectRange(0.0f),
					_attackRange(0.0f),
					_speed(0.0f),
					_targetOnSpeed(0.0f),
					_patrolX(0.0f),
					_patrolY(0.0f),
					_x(0.0f),
					_y(0.0f),
					_worldTimeCount(0.0f),
					_waitTime(0.0f),
					_waitCount(0.0f),
					_waitTimer(0.0f),
					_waitWorldTime(0.0f),
					_timeCount(0.0f),
					_isLeft(false),
					_playerX(0.0f),
					_playerY(0.0f),
					_afterAttackTime(0.0f),
					_afterAttackWorldTime(0.0f),
					_isCollisionLeft(false),
					_isCollisionRight(false),
					_isCollisionTop(false),
					_isCollisionBottom(false)
{
}

HRESULT Enemy::init(POINT position)
{
	_waitTimer = 3.0f;
	_waitWorldTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void Enemy::release(void)
{
	// Do nothing !
}

void Enemy::update(void)
{

}

void Enemy::render(void)
{

}

void Enemy::move(void)
{
}

void Enemy::targetOn(void)
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
}

bool Enemy::isWait(void)
{
	if (_waitTimer + _waitWorldTime <= TIMEMANAGER->getWorldTime())
	{
		_waitWorldTime = TIMEMANAGER->getWorldTime();
		_waitTimer = 3.0f;

		return true;
	}

	return false;
}

bool Enemy::attackCoolDown(void)
{
	return false;
}

void Enemy::pixelCollision(void)
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
