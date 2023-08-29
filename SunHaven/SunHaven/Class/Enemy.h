#pragma once
#include "../FrameWork/GameNode/GameNode.h"

#define DEGREE_RADIAN(_deg)		(PI * (_deg) / 180.f)

// Enemy (부모): 적은 이 클래스 기반으로 일반 몬스터, 보스 등 만들 수 있다
class Enemy : public GameNode
{
protected:
	GImage* _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

	float _rndFireCount;
	float _bulletFireCount;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	void draw(void);
	void animation(void);

	bool bulletCountFire(void);

	RECT getRect(void) { return _rc; }

	//void collisionCheck();

	Enemy(void);	// 자식쪽에서 호출되면서 치환 대비
	~Enemy(void) {}
};

