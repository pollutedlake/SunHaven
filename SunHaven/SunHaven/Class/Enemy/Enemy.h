#pragma once
#include "../GameNode/GameNode.h"

enum class EEnemyState
{
	IDLE,
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
	//string _strState;

public:
	HRESULT init(void);
	HRESULT init(POINT position);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	virtual void attack(void);

	virtual void draw(void);
	virtual void animation(void);

	bool bulletCountFire(void);

	RECT getRect(void) { return _rc; }

	POINT getPosition(void) { return PointMake(_x, _y); }
	void setPosition(POINT pos) { PointMake(_x, _y) = pos; }

	float getX(void) { return _x; }
	void setX(float x) { _x = x; }

	float getY(void) { return _y; }
	void setY(float y) { _y = y; }

	//void collisionCheck();

	Enemy(void);	// 자식쪽에서 호출되면서 치환 대비
	~Enemy(void) {}
};

