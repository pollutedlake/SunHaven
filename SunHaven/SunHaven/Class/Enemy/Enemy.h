#pragma once
#include "../GameNode/GameNode.h"

enum class EEnemyState
{
	IDLE,
	MOVE,
	ATTACK,
	DIE
};

class Enemy : public GameNode
{
protected:
	EEnemyState _state;

	GImage* _image;

	RECT _rc;
	float _detectRange;
	float _attackRange;

	char* _imageName;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _detectW, _detectH;
	float _timeCount;
	float _worldTimeCount;

	float _fireCount;
	float _bulletFireCount;

	bool _isLeft;

	float _playerX, _playerY;

public:
	HRESULT init(void);
	virtual HRESULT init(POINT position);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	virtual void attack(void);

	virtual void draw(void);
	virtual void animation(void);

	//bool bulletCountFire(void);

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
	void setPlayerY(float _playerY) { _playerY = _playerY; }

	//void collisionCheck();

	Enemy(void);	// 자식쪽에서 호출되면서 치환 대비
	~Enemy(void) {}
};

