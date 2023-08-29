#pragma once
#include "../FrameWork/GameNode/GameNode.h"

#define DEGREE_RADIAN(_deg)		(PI * (_deg) / 180.f)

// Enemy (�θ�): ���� �� Ŭ���� ������� �Ϲ� ����, ���� �� ���� �� �ִ�
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

	Enemy(void);	// �ڽ��ʿ��� ȣ��Ǹ鼭 ġȯ ���
	~Enemy(void) {}
};

