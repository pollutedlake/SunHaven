#pragma once
#include "../GameNode/GameNode.h"
#include "../Enemy/Enemy.h"

struct tagBullet
{
	GImage* img;
	GPImage* pImg;
	GPImage* pImg2;
	RECT rc;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
};

class Bullet : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _bulletMax;
	float _range;


public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }


	Bullet(void) {}	//차후 캐스팅 대비
	virtual ~Bullet() {}	// 언제 지워질지 알 수 없어서 가상 소멸자
};

// 빔
class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	typedef vector<tagBullet>::iterator iterBullet;	// 협업 시 재 정의
	//tagBullet bullet;
	float _range;
	float _bulletMax;

	bool _isLeft;

	int _currentFrameX;
	int _currentFrameY;

	float _worldTimeCount;

	int _index;

	float _sourX;
	float _sourX2;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float speed, int index);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	Beam() {}
	~Beam() {}
};



