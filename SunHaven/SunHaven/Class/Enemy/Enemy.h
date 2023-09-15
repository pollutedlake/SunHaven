#pragma once
#include "../GameNode/GameNode.h"
#include "../Animation/Animation.h"
#include "../UI/ProgressBar.h"

enum class EEnemyState
{
	IDLE,
	PATROL,
	TARGETON,
	ATTACK,
	DEATH
};

class Enemy : public GameNode
{
protected:
	EEnemyState _state;

	deque<pair<float, float>> _patrolPoints;
	pair<float, float> _nextPoints;

	GImage* _curImg;
	GImage* _idleImg;
	GImage* _moveImg;
	GImage* _atkImg;
	GImage* _deathImg;

	Animation* _curAni;
	Animation* _idleAni;
	Animation* _moveAni;
	Animation* _atkAni;
	Animation* _deathAni;

	GImage* _collisionMap;
	bool _isCollisionLeft;
	bool _isCollisionRight;
	bool _isCollisionTop;
	bool _isCollisionBottom;

	ProgressBar* _hpBar;
	float _hp;
	float _maxHp;

	RECT _rc;
	RECT _rcAttack;
	float _detectRange;
	float _attackRange;

	float _speed;
	float _targetOnSpeed;

	float _patrolX;
	float _patrolY;

	float _x, _y;
	float _timeCount;
	float _worldTimeCount;
	float _waitTime;
	float _waitCount;

	float _waitTimer;
	float _waitWorldTime;

	bool _isLeft;

	float _playerX, _playerY;

	float _afterAttackTime;
	float _afterAttackWorldTime;

public:
	virtual HRESULT init(POINT position);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	virtual void targetOn(void);
	virtual void attack(void);

	virtual void draw(void);

	bool isWait(void);
	virtual bool attackCoolDown(void);
	virtual void pixelCollision(void);

	EEnemyState getEState(void) { return _state; }
	void setEState(EEnemyState state) { _state = state; }

	RECT getRect(void) { return _rc; }

	POINT getPosition(void) { return PointMake(_x, _y); }
	void setPosition(POINT pos) { PointMake(_x, _y) = pos; }

	float getX(void) { return _x; }
	void setX(float x) { _x = x; }

	float getY(void) { return _y; }
	void setY(float y) { _y = y; }

	float getPlayerX(void) { return _playerX; }
	void setPlayerX(float playerX) { _playerX = playerX; }

	float getPlayerY(void) { return _playerY; }
	void setPlayerY(float playerY) { _playerY = playerY; }

	Enemy(void);
	~Enemy(void) {}
};

