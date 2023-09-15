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

}
